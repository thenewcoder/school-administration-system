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
#include "activity.h"

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

bool DatabaseManager::isUsernameTaken(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(userId) FROM user WHERE username = :name");
    query.bindValue(":name", name);

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
                  "WHERE C.className = :className "
                  "ORDER BY S.name");
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

QStringList DatabaseManager::teachersOfClass(const QString &className)
{
    QStringList teachers;

    QSqlQuery query;  // TODO: check if this query actually gets the correct values
    query.prepare("SELECT T.name FROM teacher_class TC "
                  "JOIN teacher T ON T.teacherId = TC.teacherId "
                  "JOIN class C ON C.classId = TC.classId "
                  "WHERE C.className = :className");
    query.bindValue(":className", className);

    if (query.exec())
    {
        while (query.next())
        {
            teachers.append(query.value(0).toString());
        }
    }
    else
    {
        qDebug() << "Unable to get the teachers for class " << className;
        qDebug() << query.lastError().text();
    }

    return teachers;
}

void DatabaseManager::addTeacher(const Teacher &teacher) const
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO teacher "
                          "('name', 'preferredName', gender, nationalityId, 'address', 'phoneNumber', 'photo') "
                          "VALUES(:name, :preferredName, :gender, "
                          "(SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          ":address, :phoneNumber, :photo)"));

    query.bindValue(":name", teacher.name());
    query.bindValue(":preferredName", teacher.preferredName());
    query.bindValue(":gender", teacher.gender());
    query.bindValue(":nationality", teacher.nationality());
    query.bindValue(":address", teacher.address());
    query.bindValue(":phoneNumber", teacher.phoneNumber());
    query.bindValue(":photo", teacher.photo());

    if (!query.exec())
    {
        qDebug() << "Unable to add a teacher to the database";
    }

    // get the new teacher's id
    int id = query.lastInsertId().toInt();

    // add teacher class connection
    query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES("
                  "(SELECT classId FROM class WHERE className = :className),"
                  ":teacherId)");
    for (auto &c : teacher.classesTaught())
    {
        query.bindValue(":className", c);
        query.bindValue(":teacherId", id);

        if (!query.exec())
        {
            qDebug() << "Unable to insert class teacher connection";
            qDebug() << query.lastError().text();
        }
    }
}

void DatabaseManager::addStudent(const Student &student) const
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO student "
                          "('name', 'nickName', 'dateOfBirth', gender, nationalityId, "
                          "'passportNumber', 'IDNumber', 'address', "
                          "'studentPhoneNumber', 'studentEmail', 'fathersPhoneNumber', "
                          "'mothersPhoneNumber', 'parentEmail', gradeId, 'photo', dormitoryId, busstopId) "
                          "VALUES(:name, :nickName, :dateOfBirth, :gender, "
                          "(SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          ":passportNumber, :IDNumber, :address, :studentPhoneNumber, :studentEmail, "
                          ":fathersPhoneNumber, :mothersPhoneNumber, :parentEmail, "
                          "(SELECT gradeId from grade WHERE name = :gradeName), "
                          ":photo,"
                          "(SELECT dormitoryId FROM dormitory WHERE name = :dormitory), "
                          "(SELECT busstopId FROM bus_stop WHERE busstopName = :busstop))"));

    query.bindValue(":name", student.name());
    query.bindValue(":nickName", student.nickName());
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

    // get the new student's id
    int id = query.lastInsertId().toInt();

    // add student class connection
    query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                  "(SELECT classId FROM class WHERE className = :className),"
                  ":studentId)");
    for (auto &c : student.getClassesTaken())
    {
        query.bindValue(":className", c);
        query.bindValue(":studentId", id);

        if (!query.exec())
        {
            qDebug() << "Unable to add student class connection";
            qDebug() << query.lastError().text();
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
    query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES("
                  ":classId,"
                  "(SELECT teacherId FROM teacher WHERE name = :name))");
    for (auto &t : c.teachers())
    {
        query.bindValue(":classId", classId);
        query.bindValue(":name", t);

        if (!query.exec())
        {
            qDebug() << "Unable to insert teacher in the teacher-class table";
        }
    }

    // insert the students - class connections
    query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                  ":classId,"
                  "(SELECT studentId FROM student WHERE name = :name))");
    for (auto &s : c.students())
    {
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
    const QMap<QString, int> &att = record.getAttendance();
    query.prepare("INSERT INTO attendance_record(class_record_id, studentId, attendance_type) "
                  "VALUES(:recordId,"
                  "(SELECT studentId FROM student WHERE name = :name),"
                  ":attendanceId)");

    for (auto &student : qAsConst(att))
    {
        query.bindValue(":recordId", id);
        query.bindValue(":name", att.key(student));
        query.bindValue(":attendanceId", student);

        if (!query.exec())
        {
            qDebug() << "Unable to insert an attendance record";
            qDebug() << query.lastError().text();
        }
    }
}

void DatabaseManager::addActivity(const Activity &activity)
{
    QSqlQuery query;
    query.prepare("INSERT INTO activity (code, type, name, description, teacherId, membership_limit) VALUES("
                  ":code, :type, :name, :description,"
                  "(SELECT teacherId FROM teacher WHERE name = :teacherName),"
                  ":limit)");
    query.bindValue(":code", activity.code());
    query.bindValue(":type", activity.getType());
    query.bindValue(":name", activity.name());
    query.bindValue(":description", activity.description());
    query.bindValue(":teacherName", activity.advisor());
    query.bindValue(":limit", activity.limit());

    if (!query.exec())
    {
        qDebug() << "Unable to add a new activity";
        qDebug() << query.lastError().text();
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
    query.prepare(QString("SELECT name, preferredName, gender, country, address, phoneNumber, photo FROM teacher AS T "
                          "JOIN nationality AS N ON T.nationalityId = N.nationalityId "
                          "WHERE teacherId = %1").arg(teacherId));

    if (query.exec())
    {
        while (query.next())
        {
            teacher.setName(query.value("name").toString());
            teacher.setPreferredName(query.value("preferredName").toString());
            teacher.setGender(query.value("gender").toString());
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
    query.prepare(QString("SELECT S.name, S.nickName, dateOfBirth, gender, country, passportNumber, "
                          "GR.name AS Grade, IDNumber, address, studentPhoneNumber, studentEmail, "
                          "fathersPhoneNumber, mothersPhoneNumber, parentEmail, photo, D.name AS dorm, B.busstopName AS busstop "
                          "FROM student AS S "
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
            student.setNickName(query.value("nickName").toString());
            student.setDateOfBirth(query.value("dateOfBirth").toString());
            student.setGender(query.value("gender").toString());
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
        qDebug() << "Unable to get a student";
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

            // remove any spaces from the front and end of each teacher name
            QStringList teachers = query.value("Teachers").toString().split(",");
            for (QString &t : teachers)
                t = t.trimmed();

            c.setTeachers(teachers);
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
    query.prepare("SELECT CR.date, C.className, T.name 'name' "
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
    query.prepare("SELECT S.name, attendance_type "
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

Activity DatabaseManager::getActivity(const QString &activityId)
{
    Activity activity;
    activity.setId(activityId);

    QSqlQuery query;
    query.prepare("SELECT code, A.name, type, description, T.name, membership_limit "
                  "FROM activity A "
                  "LEFT OUTER JOIN teacher T ON T.teacherId = A.teacherId "
                  "WHERE activityId = :activityId");
    query.bindValue(":activityId", activityId);

    if (query.exec())
    {
        while (query.next())
        {
            activity.setCode(query.value(0).toString());
            activity.setName(query.value(1).toString());
            activity.setType(query.value(2).toInt());
            activity.setDescription(query.value(3).toString());
            activity.setAdvisor(query.value(4).toString());
            activity.setLimit(query.value(5).toString());
        }
    }
    else
    {
        qDebug() << "Unable to get the activity data";
        qDebug() << query.lastError().text();
    }

    return activity;
}

void DatabaseManager::saveTeacherData(const Teacher &teacher, const QString &teacherId)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE teacher SET "
                          "name = :name, preferredName = :preferredName, gender = :gender, "
                          "nationalityId = (SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          "address = :address, phoneNumber = :phoneNumber, photo = :photo "
                          "WHERE teacherId = :teacherId"));

    query.bindValue(":name", teacher.name());
    query.bindValue(":preferredName", teacher.preferredName());
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
    query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES("
                  "(SELECT classId FROM class WHERE className = :className),"
                  ":teacherId)");
    for (auto &c : teacher.classesTaught())
    {
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
                          "name = :name, nickName = :nickName, dateOfBirth = :dateOfBirth, "
                          "gender = :gender, "
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
    query.bindValue(":nickName", student.nickName());
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
    query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                  "(SELECT classId FROM class WHERE className = :className),"
                  ":studentId)");
    for (auto &c : student.getClassesTaken())
    {
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
    query.prepare("INSERT INTO teacher_class(classId, teacherId) VALUES( "
                  ":classId,"
                  "(SELECT teacherId FROM teacher WHERE name = :teacherName))");
    for (auto &t : c.teachers())
    {
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
    query.prepare("INSERT INTO class_student(classId, studentId) VALUES("
                  ":classId,"
                  "(SELECT studentId FROM student WHERE name = :studentName))");
    for (auto &s : c.students())
    {
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

    const QMap<QString, int> &att = record.getAttendance();
    for (auto &student : qAsConst(att))
    {
        query.prepare(QString("UPDATE attendance_record SET "
                      "attendance_type = %1 "
                      "WHERE class_record_id = %2 AND "
                      "studentId = (SELECT studentId FROM student WHERE name = '%3')").arg(QString::number(student),
                                                                                           record.getRecordId(),
                                                                                           att.key(student)));
        if (!query.exec())
        {
            qDebug() << "Unable to update an attendance record";
            qDebug() << query.lastError().text();
        }
    }
}

void DatabaseManager::saveActivityData(const Activity &activity)
{
    QSqlQuery query;
    query.prepare("UPDATE activity SET "
                  "code = :code,"
                  "type = :type,"
                  "name = :name,"
                  "description = :description,"
                  "teacherId = (SELECT teacherId FROM teacher WHERE name = :teacherName),"
                  "membership_limit = :limit "
                  "WHERE activityId = :id");

    query.bindValue(":code", activity.code());
    query.bindValue(":type", activity.getType());
    query.bindValue(":name", activity.name());
    query.bindValue(":description", activity.description());
    query.bindValue(":teacherName", activity.advisor());
    query.bindValue(":limit", activity.limit());
    query.bindValue(":id", activity.id());

    if (!query.exec())
    {
        qDebug() << "Unable to update an activity";
        qDebug() << query.lastError().text();
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
        qDebug() << "Unable to update the user data";
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

bool DatabaseManager::removeStudent(const QString &studentId)
{
    // remove student from the class attendance_record
    if (!removeTableRows("attendance_record", "studentId", studentId))
    {
        qDebug() << "Unable to delete student's attendance record";
        return false;
    }

    // remove the student from the class_student table
    if (!removeTableRows("class_student", "studentId", studentId))
    {
        qDebug() << "Unable to delete student's class_student connection";
        return false;
    }

    // remove the student entry
    if (!removeTableRows("student", "studentId", studentId))
    {
        qDebug() << "Unable to delete student";
        return false;
    }
    return true;
}

bool DatabaseManager::removeTeacher(const QString &teacherId)
{
    // remove the teacher from class_record - attendance
    if (!clearColumnEntry("class_record", "teacherId", teacherId))
    {
        qDebug() << "Unable to remove the teacher from the class records";
        return false;
    }

    // remove the teacher from the activity table
    if (!clearColumnEntry("activity", "teacherId", teacherId))
    {
        qDebug() << "Unable to remove the teacher from activities";
        return false;
    }

    // remove teacher from teacher_class connection
    if (!removeTableRows("teacher_class", "teacherId", teacherId))
    {
        qDebug() << "Unable to delete teacher's teacher_class connection";
        return false;
    }

    // remove teacher entry
    if (!removeTableRows("teacher", "teacherId", teacherId))
    {
        qDebug() << "Unable to delete teacher";
        return false;
    }
    return true;
}

bool DatabaseManager::removeClass(const QString &classId)
{
    // remove record from teacher_class table
    if (!removeTableRows("teacher_class", "classId", classId))
    {
        qDebug() << "Unable to delete class reference from teacher_class table";
        return false;
    }

    // remove class from class_student table
    if (!removeTableRows("class_student", "classId", classId))
    {
        qDebug() << "Unable to delete class reference from class_student table";
        return false;
    }

    // remove class from the class_record table
    if (!removeTableRows("class_record", "classId", classId))
    {
        qDebug() << "Unable to delete class reference from class_record";
        return false;
    }

    // finally remove class from class table
    if (!removeTableRows("class", "classId", classId))
    {
        qDebug() << "classId to delete:" << classId;
        qDebug() << "Unable to delete from class table";
        return false;
    }
    return true;
}

bool DatabaseManager::removeGrade(const QString &grade)
{
    QSqlQuery query;

    // remove the grade connection to the class table
    query.prepare("UPDATE class SET "
                  "gradeId = NULL "
                  "WHERE gradeId = (SELECT gradeId FROM grade WHERE name = :grade)");
    query.bindValue(":grade", grade);

    if (!query.exec())
    {
        qDebug() << "Unable to delete grade association in the class table";
        qDebug() << query.lastError().text();
        return false;
    }

    // remove the grade connection to the student table
    query.prepare("UPDATE student SET "
                  "gradeId = NULL "
                  "WHERE gradeId = (SELECT gradeId FROM grade WHERE name = :grade)");
    query.bindValue(":grade", grade);

    if (!query.exec())
    {
        qDebug() << "Unable to delete grade association in the student table";
        qDebug() << query.lastError().text();
        return false;
    }

    // remove the grade record
    if (!removeTableRows("grade", "name", grade))
    {
        qDebug() << "Unable to delete grade:" << grade;
        return false;
    }
    return true;
}

bool DatabaseManager::removeSubject(const QString &subject)
{
    // remove the subject connection to the class table
    QSqlQuery query;
    query.prepare("UPDATE class SET "
                  "subjectId = NULL "
                  "WHERE subjectId = (SELECT subjectId FROM subject WHERE subjectName = :subject)");
    query.bindValue(":subject", subject);

    if (!query.exec())
    {
        qDebug() << "Unable to remove subject association to the class table";
        qDebug() << query.lastError().text();
        return false;
    }

    // remove the subject
    if (!removeTableRows("subject", "subjectName", subject))
    {
        qDebug() << "Unable to delete subject:" << subject;
        return false;
    }
    return true;
}

bool DatabaseManager::removeTableRows(const QString &table, const QString &col, const QString &id)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM `%1` WHERE `%2` = '%3'").arg(table, col, id));

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
    bool op1 = removeTableRows("attendance_record", "class_record_id", recordId);

    // remove row from class_record
    bool op2 = removeTableRows("class_record", "recordId", recordId);

    return op1 && op2;
}

bool DatabaseManager::removeActivity(const QString &activityId)
{
    return removeTableRows("activity", "activityId", activityId);
}

bool DatabaseManager::clearColumnEntry(const QString &table, const QString &col, const QString &id)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET "
                          "%2 = NULL "
                          "WHERE %2 = %3").arg(table, col, id));

    if (!query.exec())
    {
        qDebug() << "Unable to clear the column entry";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    }
    return true;
}

bool DatabaseManager::removeClassroom(const QString &roomId)
{
    // remove classroom connection from the class table
    if (!clearColumnEntry("class", "classroomId", roomId))
    {
        qDebug() << "Unable to remove classroom association to class table";
        return false;
    }

    // remove the classroom
    if (!removeTableRows("classroom", "classroomId", roomId))
    {
        qDebug() << "Unable to delete a classroom";
        return false;
    }
    return true;
}

bool DatabaseManager::removeBusstop(const QString &busstopId)
{
    // remove bus stop connections to the student table
    if (!clearColumnEntry("student", "busstopId", busstopId))
    {
        qDebug() << "Unable to remove association in the student table";
        return false;
    }

    // remove the bus stop
    if (!removeTableRows("bus_stop", "busstopId", busstopId))
    {
        qDebug() << "Unable to delete a bus stop";
        return false;
    }
    return true;
}

bool DatabaseManager::removeDormitory(const QString &dormId)
{
    // remove dormitory connection from student table
    if (!clearColumnEntry("student", "dormitoryId", dormId))
    {
        qDebug() << "Unable to remove association to student table";
        return false;
    }

    // remove the dormitory
    if (!removeTableRows("dormitory", "dormitoryId", dormId))
    {
        qDebug() << "Unable to remove dormitory";
        return false;
    }
    return true;
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
    QStringList sql = in.readAll().split(";", QString::SkipEmptyParts);

    for (const QString &statement : qAsConst(sql))
    {
        if (statement.trimmed() != "")
        {
            QSqlQuery query;
            query.exec(statement);
        }
    }
    file.close();
}
