#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

#include "settings.h"

#include "teacher.h"
#include "student.h"
#include "school.h"
#include "user.h"
#include "class.h"
#include "classrecord.h"

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
}

bool DatabaseManager::validateLogin(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM user WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec() || !query.first())
    {
        return false;
    }
    else if (query.value(0).toInt() == 0)
    {
        return false;
    }
    return true;
}

int DatabaseManager::numClasses() const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(classId) FROM class");
    if (query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }
    return 0;
}

int DatabaseManager::numTeachers() const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(teacherId) FROM teacher");
    if (query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }
    return 0;
}

int DatabaseManager::numStudents() const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(studentId) FROM student");
    if (query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }
    return 0;
}

QStringList DatabaseManager::nationalities() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT country FROM nationality");
    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    return list;
}

QStringList DatabaseManager::dormitories() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT name FROM dormitory ORDER BY name");
    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    return list;
}

QStringList DatabaseManager::busstops() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT busstopName FROM bus_stop ORDER BY busstopName");
    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    return list;
}

QStringList DatabaseManager::subjects() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT subjectName FROM subject ORDER BY subjectName DESC");

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get the subjects";
    }

    return list;
}

QStringList DatabaseManager::classrooms() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT classroomName FROM classroom ORDER BY classroomName DESC");

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get the classoom names";
    }

    return list;
}

QStringList DatabaseManager::teachers() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT name FROM teacher");

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get all the teachers";
    }
    return list;
}

QStringList DatabaseManager::students() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT name FROM student");

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get all the students";
    }
    return list;
}

// returns all classes in the database
QStringList DatabaseManager::classes() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT className from class");

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get all the classes";
    }
    return list;
}

QStringList DatabaseManager::grades() const
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT name FROM grade");

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get all the grades";
    }
    return list;
}

QStringList DatabaseManager::studentsOfClass(const QString &className)
{
    QStringList students;

    QSqlQuery query;
    query.prepare("SELECT S.name FROM class_student CS "
                  "LEFT OUTER JOIN student S ON S.studentId = CS.studentId "
                  "LEFT OUTER JOIN class C ON C.classId = CS.classId "
                  "WHERE C.className = :className");
    query.bindValue(":className", className);

    if (query.exec())
    {
        while (query.next())
        {
            students.append(query.value(0).toString());
        }
    }
    else
    {
        qDebug() << "Unable to get the students of the class:" << className;
        qDebug() << query.lastError().text();
    }

    return students;
}

void DatabaseManager::addTeacher(const Teacher &teacher) const
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO teacher "
                          "('name', genderId, nationalityId, 'address', 'phoneNumber', 'photo') "
                          "VALUES(:name, "
                          "(SELECT genderId FROM gender WHERE type = :gender), "
                          "(SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          ":address, :phoneNumber, :photo)"));

    query.bindValue(":name", teacher.name());
    query.bindValue(":gender", teacher.gender());
    query.bindValue(":nationality", teacher.nationality());
    query.bindValue(":address", teacher.address());
    query.bindValue(":phoneNumber", teacher.phoneNumber());
    query.bindValue(":photo", teacher.photo());

    if (!query.exec())
    {
        qDebug() << "Unable to add a teacher to the database";
    }

    // add teacher class connection
    for (auto &c : teacher.classesTaught())
    {
        query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES("
                      "(SELECT classId FROM class WHERE className = :className),"
                      ":teacherId)");
        query.bindValue(":className", c);
        query.bindValue(":teacherId", teacher.id());

        if (!query.exec())
        {
            qDebug() << "Unable to insert class teacher connection";
        }
    }
}

void DatabaseManager::addStudent(const Student &student) const
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO student "
                          "('name', 'dateOfBirth', genderId, nationalityId, "
                          "'passportNumber', 'IDNumber', 'address', "
                          "'studentPhoneNumber', 'studentEmail', 'fathersPhoneNumber', "
                          "'mothersPhoneNumber', 'parentEmail', gradeId, 'photo', dormitoryId, busstopId) "
                          "VALUES(:name, :dateOfBirth, "
                          "(SELECT genderId FROM gender WHERE type = :gender), "
                          "(SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          ":passportNumber, :IDNumber, :address, :studentPhoneNumber, :studentEmail, "
                          ":fathersPhoneNumber, :mothersPhoneNumber, :parentEmail, "
                          "(SELECT gradeId from grade WHERE name = :gradeName), "
                          ":photo,"
                          "(SELECT dormitoryId FROM dormitory WHERE name = :dormitory), "
                          "(SELECT busstopId FROM bus_stop WHERE busstopName = :busstop))"));

    query.bindValue(":name", student.name());
    query.bindValue(":dateOfBirth", student.dateOfBirth());
    query.bindValue(":gender", student.gender());
    query.bindValue(":nationality", student.nationality());
    query.bindValue(":passportNumber", student.passportNumber());
    query.bindValue(":IDNumber", student.iDNumber());
    query.bindValue(":address", student.address());
    query.bindValue(":studentPhoneNumber", student.studentPhoneNumber());
    query.bindValue(":studentEmail", student.studentEmail());
    query.bindValue(":fathersPhoneNumber", student.fathersPhoneNumber());
    query.bindValue(":mothersPhoneNumber", student.mothersPhoneNumber());
    query.bindValue(":parentEmail", student.parentsEmail());
    query.bindValue(":gradeName", student.getGrade());
    query.bindValue(":photo", student.photo());
    query.bindValue(":dormitory", student.dormitory());
    query.bindValue(":busstop", student.busstop());

    if (!query.exec())
    {
        qDebug() << "Unable to add a new student";
        qDebug() << query.lastError().text();
    }

    // add student class connection
    for (auto &c : student.getClassesTaken())
    {
        query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                      "(SELECT classId FROM class WHERE className = :className),"
                      ":studentId)");
        query.bindValue(":className", c);
        query.bindValue(":studentId", student.getId());

        if (!query.exec())
        {
            qDebug() << "Unable to add student class connection";
        }
    }
}

void DatabaseManager::addClass(const Class &c) const
{
    QSqlQuery query;

    // insert the class
    query.prepare("INSERT INTO class(gradeId, className, subjectId, classroomId) VALUES("
                  "(SELECT gradeId FROM grade WHERE name = :gradeName), "
                  ":className, "
                  "(SELECT subjectId FROM subject WHERE subjectName = :subjectName), "
                  "(SELECT classroomId FROM classroom WHERE classroomName = :classroomName))");
    /*"WHERE EXISTS (SELECT subjectId FROM subject WHERE subjectName = :subjectName) "
                  "AND (SELECT classroomId FROM classroom WHERE classroomName = :classroomName))");*/

    query.bindValue(":gradeName", c.getGrade());
    query.bindValue(":className", c.className());
    query.bindValue(":subjectName", c.subject());
    query.bindValue(":classroomName", c.classRoom());
    if (!query.exec())
    {
        qDebug() << "Unable to insert class";
        qDebug() << query.lastError().text();
        return;
    }

    // get the new class id
    QString classId = query.lastInsertId().toString();

    // insert the teachers - class connections
    for (auto &t : c.teachers())
    {
        query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES("
                      ":classId,"
                      "(SELECT teacherId FROM teacher WHERE name = :name))");
        query.bindValue(":classId", classId);
        query.bindValue(":name", t);

        if (!query.exec())
        {
            qDebug() << "Unable to insert teacher in the teacher-class table";
        }
    }

    // insert the students - class connections
    for (auto &s : c.students())
    {
        query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                      ":classId,"
                      "(SELECT studentId FROM student WHERE name = :name))");
        query.bindValue(":classId", classId);
        query.bindValue(":name", s);

        if (!query.exec())
        {
            qDebug() << "Unable to insert student into the class_student table";
        }
    }

}

void DatabaseManager::addClassoom(const QString &name, const QString &comment)
{
    QSqlQuery query;
    query.prepare("INSERT INTO classroom(classroomName, description) VALUES("
                  ":name, :comment)");
    query.bindValue(":name", name);
    query.bindValue(":comment", comment);

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new classroom";
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::addDormitory(const QString &name, const QString &comment)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dormitory(name, description) VALUES("
                  ":name, :comment)");
    query.bindValue(":name", name);
    query.bindValue(":comment", comment);

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new dormitory";
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::addBusstop(const QString &name, const QString &comment)
{
    QSqlQuery query;
    query.prepare("INSERT INTO bus_stop(busstopName, description) VALUES("
                  ":name, :comment)");
    query.bindValue(":name", name);
    query.bindValue(":comment", comment);

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new bus stop";
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::addGrade(const QString &name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO grade(name) VALUES("
                  ":name)");
    query.bindValue(":name", name);

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new grade";
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::addSubject(const QString &name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO subject(subjectName) VALUES("
                  ":name)");
    query.bindValue(":name", name);

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new subject";
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::addUser(const QString &username, const QString &password, const QString &fullname)
{
    QSqlQuery query;
    // for now don't deal with the userTypeId
    query.prepare("INSERT INTO user (username, password, fullname) VALUES("
                  ":username, :password, :fullname)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":fullname", fullname);

    if (!query.exec())
    {
        qDebug() << "Unable to insert new user";
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::addUser(const User &user)
{
    addUser(user.username(), user.password(), user.fullName());
}

void DatabaseManager::addClassRecord(const ClassRecord &record)
{
    QSqlQuery query;
    query.prepare("INSERT INTO class_record(date, classId, teacherId) VALUES("
                  ":date,"
                  "(SELECT classId FROM class WHERE className = :className),"
                  "(SELECT teacherId FROM teacher WHERE name = :teacherName))");
    query.bindValue(":date", record.getDate());
    query.bindValue(":className", record.getClass());
    query.bindValue(":teacherName", record.getTeacher());

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new class record";
        qDebug() << query.lastError().text();
    }

    // get the last id
    int id = query.lastInsertId().toInt();

    // add the attendance
    QMap<QString, int> &att = record.getAttendance();
    for (auto &student : att.keys())
    {
        query.prepare("INSERT INTO attendance_record(class_record_id, studentId, attendance_type_id) "
                      "VALUES(:recordId,"
                      "(SELECT studentId FROM student WHERE name = :name),"
                      ":attendanceId)");
        query.bindValue(":recordId", id);
        query.bindValue(":name", student);
        query.bindValue(":attendanceId", att.value(student));

        if (!query.exec())
        {
            qDebug() << "Unable to insert an attendance record";
            qDebug() << query.lastError().text();
        }
    }
}

User DatabaseManager::getUser(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT userId, password, fullname FROM user WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec())
    {
        query.next();
        return User(query.value("userId").toString(),
                    username,
                    query.value("password").toString(),
                    query.value("fullname").toString());
    }
    qDebug() << "Unable to get the user data";
    return User();
}

School DatabaseManager::getSchoolInfo() const
{
    School school;

    QSqlQuery query;
    query.prepare("SELECT * FROM school");
    if (query.exec())
    {
        query.next();

        school.setSchoolName(query.value("name").toString());
        school.setSchoolAddress(query.value("address").toString());
        school.setSchoolPhone(query.value("phone").toString());
        school.setSchoolEmail(query.value("email").toString());
        school.setSchoolLogo(query.value("logo").toByteArray());

        return school;
    }

    qDebug() << "Unable to get school Info";
    qDebug() << query.lastError().text();

    return school;
}

Teacher DatabaseManager::getTeacher(const QString &teacherId)
{
    Teacher teacher;

    QSqlQuery query;
    query.prepare(QString("SELECT name, type, country, address, phoneNumber, photo FROM teacher AS T "
                          "JOIN gender AS G ON T.genderId = G.genderId "
                          "JOIN nationality AS N ON T.nationalityId = N.nationalityId "
                          "WHERE teacherId = %1").arg(teacherId));

    if (query.exec())
    {
        while (query.next())
        {
            teacher.setName(query.value("name").toString());
            teacher.setGender(query.value("type").toString());
            teacher.setNationality(query.value("country").toString());
            teacher.setAddress(query.value("address").toString());
            teacher.setPhoneNumber(query.value("phoneNumber").toString());
            teacher.setPhoto(query.value("photo").toByteArray());
        }
    }

    return teacher;
}

Student DatabaseManager::getStudent(const QString &studentId)
{
    Student student;

    QSqlQuery query;
    query.prepare(QString("SELECT S.name, dateOfBirth, type, country, passportNumber, "
                          "GR.name AS Grade, IDNumber, address, studentPhoneNumber, studentEmail, "
                          "fathersPhoneNumber, mothersPhoneNumber, parentEmail, photo, D.name AS dorm, B.busstopName AS busstop "
                          "FROM student AS S "
                          "LEFT OUTER JOIN gender AS G ON S.genderId = G.genderId "
                          "LEFT OUTER JOIN nationality AS N ON S.nationalityId = N.nationalityId "
                          "LEFT OUTER JOIN dormitory AS D ON D.dormitoryId = S.dormitoryId "
                          "LEFT OUTER JOIN bus_stop AS B ON B.busstopId = S.busstopId "
                          "LEFT OUTER JOIN grade AS GR ON GR.gradeId = S.gradeId "
                          "WHERE studentId = %1").arg(studentId));
    if (query.exec())
    {
        if (query.next())
        {
            student.setId(studentId);
            student.setName(query.value("name").toString());
            student.setDateOfBirth(query.value("dateOfBirth").toString());
            student.setGender(query.value("type").toString());
            student.setNationality(query.value("country").toString());
            student.setGrade(query.value("Grade").toString());
            student.setPassportNumber(query.value("passportNumber").toString());
            student.setIDNumber(query.value("IDNumber").toString());
            student.setAddress(query.value("address").toString());
            student.setStudentPhoneNumber(query.value("studentPhoneNumber").toString());
            student.setStudentEmail(query.value("studentEmail").toString());
            student.setFathersPhoneNumber(query.value("fathersPhoneNumber").toString());
            student.setMothersPhoneNumber(query.value("mothersPhoneNumber").toString());
            student.setParentsEmail(query.value("parentEmail").toString());
            student.setPhoto(query.value("photo").toByteArray());
            student.setDormitory(query.value("dorm").toString());
            student.setBusstop(query.value("busstop").toString());
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return student;
}

Class DatabaseManager::getClass(const QString &classId)
{
    Class c;
    c.setClassId(classId);

    QSqlQuery query;
    query.prepare("SELECT grade, className, subjectName, classroomName, Teachers "
                  "FROM class_summary "
                  "WHERE classId = :classId");

    query.bindValue(":classId", classId);

    if (query.exec())
    {
        if (query.next())
        {
            c.setGrade(query.value("grade").toString());
            c.setClassname(query.value("className").toString());
            c.setSubject(query.value("subjectName").toString());
            c.setClassroom(query.value("classroomName").toString());
            c.setTeachers(query.value("Teachers").toString().split(","));
        }
    }
    else
    {
        qDebug() << "Unable to get class data";
    }

    query.prepare("SELECT group_concat(S.name, ', ') AS Students FROM class_student CS "
                  "JOIN student S ON S.studentId = CS.studentId "
                  "WHERE classId = :classId");

    query.bindValue(":classId", classId);
    if (query.exec())
    {
        query.next();
        c.setStudents(query.value("Students").toString().split(", "));
    }
    else
    {
        qDebug() << "Unable to get students for class data";
        qDebug() << query.lastError().text();
    }

    return c;
}

ClassRecord DatabaseManager::getClassRecord(const QString &recordId)
{
    ClassRecord record;
    record.setRecordId(recordId);

    QSqlQuery query;
    query.prepare("SELECT CR.date, C.className, T.name "
                  "FROM class_record CR "
                  "LEFT OUTER JOIN class C ON C.classId = CR.classId "
                  "LEFT OUTER JOIN teacher T ON T.teacherId = CR.teacherId "
                  "WHERE recordId = :recordId");
    query.bindValue(":recordId", recordId);

    if (query.exec())
    {
        if (query.next())
        {
            record.setClass(query.value("className").toString());
            record.setDate(query.value("date").toString());
            record.setTeacher(query.value("name").toString());
        }
    }
    else
    {
        qDebug() << "Unable to get a class record";
        qDebug() << query.lastError().text();
    }

    // get the attendance records
    query.prepare("SELECT S.name, attendance_type_id "
                  "FROM attendance_record AR "
                  "LEFT OUTER JOIN student S ON S.studentId = AR.studentId "
                  "WHERE class_record_id = :recordId");
    query.bindValue(":recordId", recordId);

    if (query.exec())
    {
        while (query.next())
        {
            record.addAttendanceRecord(query.value(0).toString(),  // name
                                       query.value(1).toInt());    //  attendance type
        }
    }
    else
    {
        qDebug() << "Unable to get the attendance records";
        qDebug() << query.lastError().text();
    }

    return record;
}

void DatabaseManager::saveTeacherData(const Teacher &teacher, const QString &teacherId)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE teacher SET "
                          "name = :name, genderId = (SELECT genderId FROM gender WHERE type = :gender), "
                          "nationalityId = (SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          "address = :address, phoneNumber = :phoneNumber, photo = :photo "
                          "WHERE teacherId = :teacherId"));

    query.bindValue(":name", teacher.name());
    query.bindValue(":gender", teacher.gender());
    query.bindValue(":nationality", teacher.nationality());
    query.bindValue(":address", teacher.address());
    query.bindValue(":phoneNumber", teacher.phoneNumber());
    query.bindValue(":photo", teacher.photo());
    query.bindValue(":teacherId", teacherId);

    if (!query.exec())
    {
        qDebug() << "Unable to update teacher data";
    }

    // Update the class teacher connection
    // first delete the old connections
    if (!removeTableRows("teacher_class", "teacherId", teacherId))
    {
        qDebug() << "Unable to delete teacher class connection";
    }

    // add the new connections
    for (auto &c : teacher.classesTaught())
    {
        query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES("
                      "(SELECT classId FROM class WHERE className = :className),"
                      ":teacherId)");
        query.bindValue(":className", c);
        query.bindValue(":teacherId", teacherId);

        if (!query.exec())
        {
            qDebug() << "Unable to insert the new teacher class connections";
        }
    }
}

void DatabaseManager::saveStudentData(const Student &student, const QString &studentId)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE student SET "
                          "name = :name, dateOfBirth = :dateOfBirth, "
                          "genderId = (SELECT genderId FROM gender WHERE type = :gender), "
                          "nationalityId = (SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          "passportNumber = :passportNumber, IDNumber = :IDNumber, "
                          "address = :address, studentPhoneNumber = :studentPhoneNumber, "
                          "studentEmail = :studentEmail, fathersPhoneNumber = :fathersPhoneNumber, "
                          "mothersPhoneNumber = :mothersPhoneNumber, parentEmail = :parentEmail, "
                          "gradeId = (SELECT gradeId FROM grade WHERE name = :gradeName), "
                          "photo = :photo, "
                          "dormitoryId = (SELECT dormitoryId FROM dormitory WHERE name = :dormitory), "
                          "busstopId = (SELECT busstopId FROM bus_stop WHERE busstopName = :busstopName) "
                          "WHERE studentId = :studentId"));

    query.bindValue(":name", student.name());
    query.bindValue(":dateOfBirth", student.dateOfBirth());
    query.bindValue(":gender", student.gender());
    query.bindValue(":nationality", student.nationality());
    query.bindValue(":passportNumber", student.passportNumber());
    query.bindValue(":IDNumber", student.iDNumber());
    query.bindValue(":address", student.address());
    query.bindValue(":studentPhoneNumber", student.studentPhoneNumber());
    query.bindValue(":studentEmail", student.studentEmail());
    query.bindValue(":fathersPhoneNumber", student.fathersPhoneNumber());
    query.bindValue(":mothersPhoneNumber", student.mothersPhoneNumber());
    query.bindValue(":parentEmail", student.parentsEmail());
    query.bindValue(":gradeName", student.getGrade());
    query.bindValue(":studentId", studentId);
    query.bindValue(":photo", student.photo());
    query.bindValue(":dormitory", student.dormitory());
    query.bindValue(":busstopName", student.busstop());

    if (!query.exec())
    {
        qDebug() << "Unable to update student data";
        qDebug() << query.lastError().text();
    }

    // update the student class connection
    // start by remove all and start from scratch
    if (!removeTableRows("class_student", "studentId", studentId))
    {
        qDebug() << "Unable to remove class connection in saveStudentData";
        qDebug() << "studentId" << studentId;
    }

    // update with the new connections
    for (auto &c : student.getClassesTaken())
    {
        query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                      "(SELECT classId FROM class WHERE className = :className),"
                      ":studentId)");
        query.bindValue(":className", c);
        query.bindValue(":studentId", studentId);

        if (!query.exec())
        {
            qDebug() << "Unable to insert the new class values";
        }
    }
}

void DatabaseManager::saveSchoolData(const School &school)
{
    QSqlQuery query;
    query.prepare("UPDATE school SET "
                  "name = :name, address = :address, phone = :phone, "
                  "email = :email, logo = :logo");

    query.bindValue(":name", school.schoolName());
    query.bindValue(":address", school.schoolAddress());
    query.bindValue(":phone", school.schoolPhone());
    query.bindValue(":email", school.schoolEmail());
    query.bindValue(":logo", school.schoolLogo());

    if (!query.exec())
    {
        qDebug() << "Unable to save school data";
        qDebug() << query.lastError().text();
    }
    qDebug() << "Saved school data";
}

void DatabaseManager::saveClassData(const Class &c)
{
    QSqlQuery query;

    // first update the class table
    query.prepare("UPDATE class SET "
                  "gradeId = (SELECT gradeId FROM grade WHERE name = :gradeName),"
                  "className = :className,"
                  "subjectId = (SELECT subjectId FROM subject WHERE subjectName = :subjectName),"
                  "classroomId = (SELECT classroomId FROM classroom WHERE classroomName = :classroomName) "
                  "WHERE classId = :classId");
    query.bindValue(":gradeName", c.getGrade());
    query.bindValue(":className", c.className());
    query.bindValue(":subjectName", c.subject());
    query.bindValue(":classroomName", c.classRoom());
    query.bindValue(":classId", c.classId());

    if (!query.exec())
    {
        qDebug() << "Unable to update the class table";
        qDebug() << query.lastError().text();
        return;
    }

    // update the teacher-class table
    // first delete all teachers with the classId (is there a better way??)
    if (!removeTableRows("teacher_class", "classId", c.classId()))
    {
        qDebug() << "Unable to delete teachers";
    }

    // then insert all the teachers
    for (auto &t : c.teachers())
    {
        query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES( "
                      ":classId,"
                      "(SELECT teacherId FROM teacher WHERE name = :teacherName))");
        query.bindValue(":classId", c.classId());
        query.bindValue(":teacherName", t);

        if (!query.exec())
        {
            qDebug() << "Unable to insert teacher into teacher_class table";
        }
    }

    // update all the students
    //first delete all the students with the classId (any better way??)
    if (!removeTableRows("class_student", "classId", c.classId()))
    {
        qDebug() << "Unable to delete students";
    }

    // insert the students
    for (auto &s : c.students())
    {
        query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                      ":classId,"
                      "(SELECT studentId FROM student WHERE name = :studentName))");
        query.bindValue(":classId", c.classId());
        query.bindValue(":studentName", s);

        if (!query.exec())
        {
            qDebug() << "Unable to insert student into class_student table";
            qDebug() << query.lastError().text();
        }
    }
}

void DatabaseManager::saveClassRecord(const ClassRecord &record)
{
    QSqlQuery query;
    query.prepare("UPDATE class_record SET "
                  "date = :date, "
                  "classId = (SELECT classId FROM class WHERE className = :className), "
                  "teacherId = (SELECT teacherId FROM teacher WHERE name = :teacherName) "
                  "WHERE recordId = :recordId");
    query.bindValue(":date", record.getDate());
    query.bindValue(":className", record.getClass());
    query.bindValue(":teacherName", record.getTeacher());
    query.bindValue(":recordId", record.getRecordId());

    if (!query.exec())
    {
        qDebug() << "Unable to update a class record";
        qDebug() << query.lastError().text();
    }

    // update the existing attendance records

    QMap<QString, int> &att = record.getAttendance();
    for (auto &student : att.keys())
    {

        query.prepare(QString("UPDATE attendance_record SET "
                      "attendance_type_id = %1 "
                      "WHERE class_record_id = %2 AND "
                      "studentId = (SELECT studentId FROM student WHERE name = '%3')").arg(QString::number(att.value(student)),
                                                                                           record.getRecordId(),
                                                                                           student));
        if (!query.exec())
        {
            qDebug() << "Unable to update an attendance record";
            qDebug() << query.lastError().text();
        }
    }
}

bool DatabaseManager::updateUserData(const User &user)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET "
                  "username = :username,"
                  "password = :password,"
                  "fullname = :fullname "
                  "WHERE userId = :userid");
    query.bindValue(":username", user.username());
    query.bindValue(":password", user.password());
    query.bindValue(":fullname", user.fullName());
    query.bindValue(":userid", user.userId());

    if (!query.exec())
    {
        qDebug() << "Unable to udpate the user data";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateClassroom(const QString &id, const QString &name, const QString &comment)
{
    QSqlQuery query;
    query.prepare("UPDATE classroom SET "
                  "classroomName = :name,"
                  "description = :comment "
                  "WHERE classroomId = :id");
    query.bindValue(":name", name);
    query.bindValue(":comment", comment);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Unable to update classroom data";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateDormitory(const QString &id, const QString &name, const QString &comment)
{
    QSqlQuery query;
    query.prepare("UPDATE dormitory SET "
                  "name = :name,"
                  "description = :comment "
                  "WHERE dormitoryId = :id");
    query.bindValue(":name", name);
    query.bindValue(":comment", comment);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Unable to update dormitory data";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateBusstop(const QString &id, const QString &name, const QString &comment)
{
    QSqlQuery query;
    query.prepare("UPDATE bus_stop SET "
                  "busstopName = :name,"
                  "description = :comment "
                  "WHERE busstopId = :id");
    query.bindValue(":name", name);
    query.bindValue(":comment", comment);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Unable to update bus stop data";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateGrade(const QString &oldName, const QString &newName)
{
    QSqlQuery query;
    query.prepare("UPDATE grade SET "
                  "name = :newName "
                  "WHERE name = :oldName");
    query.bindValue(":newName", newName);
    query.bindValue(":oldName", oldName);

    if (!query.exec())
    {
        qDebug() << "Unable to update grade data";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateSubject(const QString &oldName, const QString &newName)
{
    QSqlQuery query;
    query.prepare("UPDATE subject SET "
                  "subjectName = :newName "
                  "WHERE subjectName = :oldName");
    query.bindValue(":newName", newName);
    query.bindValue(":oldName", oldName);

    if (!query.exec())
    {
        qDebug() << "Unable to update subject data";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::removeStudent(const QString &studentId)
{
    // remove the student from the class_student table
    if (!removeTableRows("class_student", "studentId", studentId))
    {
        qDebug() << "Unable to delete student's class_student connection";
    }

    // remove the student entry
    if (!removeTableRows("student", "studentId", studentId))
    {
        qDebug() << "Unable to delete student";
    }
}

void DatabaseManager::removeTeacher(const QString &teacherId)
{
    // remove teacher from teacher_class connection
    if (!removeTableRows("teacher_class", "teacherId", teacherId))
    {
        qDebug() << "Unable to delete teacher's teacher_class connection";
    }

    // remove teacher entry
    if (!removeTableRows("teacher", "teacherId", teacherId))
    {
        qDebug() << "Unable to delete teacher";
    }
}

void DatabaseManager::removeClass(const QString &classId)
{
    // remove record from teacher_class table
    if (!removeTableRows("teacher_class", "classId", classId))
    {
        qDebug() << "Unable to delete class reference from teacher_class table";
    }

    // remove record from class_student table
    if (!removeTableRows("class_student", "classId", classId))
    {
        qDebug() << "Unable to delete class reference from class_student table";
    }

    // finally remove record from class table
    if (!removeTableRows("class", "classId", classId))
    {
        qDebug() << "classId to delete:" << classId;
        qDebug() << "Unable to delete from class table";
        return;
    }
}

void DatabaseManager::removeGrade(const QString &grade)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM grade WHERE name = '%1'").arg(grade));

    if (!query.exec())
    {
        qDebug() << "Unable to delete grade:" << grade;
        qDebug() << query.lastError().text();
    }
}

void DatabaseManager::removeSubject(const QString &subject)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM subject WHERE subjectName = '%1'").arg(subject));

    if (!query.exec())
    {
        qDebug() << "Unable to delete subject:" << subject;
        qDebug() << query.lastError().text();
    }
}

bool DatabaseManager::removeTableRows(const QString &table, const QString &col, const QString &id)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE %2 = %3").arg(table, col, id));

    if (!query.exec())
    {
        qDebug() << "Unable to remove from" << table;
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::removeClassRecord(const QString &recordId)
{
    // remove rows from attendance_record with the recordId
    bool op2 = removeTableRows("attendance_record", "class_record_id", recordId);

    // remove row from class_record
    bool op1 = removeTableRows("class_record", "recordId", recordId);

    return op1 && op2;
}

QStringList DatabaseManager::classesTaken(const QString &id)
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT className FROM class_student CS "
                  "JOIN class C ON C.classId = CS.classId "
                  "JOIN subject SJ ON C.subjectId = SJ.subjectId "
                  "WHERE studentId = :studentId");
    query.bindValue(":studentId", id);

    if (query.exec())
    {
        while (query.next())
            list << query.value("className").toString();
    }
    else
    {
        qDebug() << "Unable to get the classes";
        qDebug() << query.lastError().text();
    }

    return list;
}

QStringList DatabaseManager::classesTaught(const QString &id)
{
    QStringList list;

    QSqlQuery query;
    query.prepare("SELECT className FROM teacher_class TC "
                  "JOIN class C ON C.classId = TC.classId "
                  "JOIN subject SJ ON C.subjectId = SJ.subjectId "
                  "WHERE teacherId = :teacherId");
    query.bindValue(":teacherId", id);

    if (query.exec())
    {
        while (query.next())
        {
            list << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Unable to get all the classes taught by teacher";
    }
    return list;
}

DatabaseManager::DatabaseManager(const QString &path)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase(Settings::instance().databaseDriver())))
{
    // TODO: change the way this is handled - eg. deal with locale issues
    // determine the location of the database - TODO: make it better later
    QString location = Settings::instance().databaseLocation();
    if (location.isEmpty())
        location = path;

    mDatabase->setDatabaseName(location);

    // add better error checking later
    if (!mDatabase->open())
    {
        qDebug() << "Unable to open database";
        // TODO: add code to let the user search for the database or perhaps go through the wizard again
    }

    // create new tables if none exist
    if (mDatabase->tables().count() < 1)
        createDatabase();

    // turn on foreign key support
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys=ON");
}

void DatabaseManager::createDatabase()
{
    QFile file(":/sql/sql/databaseCreationScript.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString sql = in.readAll();

    for (const QString &statement : sql.split(";", QString::SkipEmptyParts))
    {
        if (statement.trimmed() != "")
        {
            QSqlQuery query;
            query.exec(statement);
        }
    }
    file.close();
}
