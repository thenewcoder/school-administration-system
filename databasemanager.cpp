#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "teacher.h"
#include "student.h"
#include "school.h"
#include "user.h"
#include "class.h"

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
                          "'mothersPhoneNumber', 'parentEmail', 'photo', dormitoryId, busstopId) "
                          "VALUES(:name, :dateOfBirth, "
                          "(SELECT genderId FROM gender WHERE type = :gender), "
                          "(SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          ":passportNumber, :IDNumber, :address, :studentPhoneNumber, :studentEmail, "
                          ":fathersPhoneNumber, :mothersPhoneNumber, :parentEmail, :photo,"
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
    query.prepare("INSERT INTO class(className, subjectId, classroomId) VALUES("
                  ":className, "
                  "(SELECT subjectId FROM subject WHERE subjectName = :subjectName), "
                  "(SELECT classroomId FROM classroom WHERE classroomName = :classroomName))");
    /*"WHERE EXISTS (SELECT subjectId FROM subject WHERE subjectName = :subjectName) "
                  "AND (SELECT classroomId FROM classroom WHERE classroomName = :classroomName))");*/

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
                          "IDNumber, address, studentPhoneNumber, studentEmail, "
                          "fathersPhoneNumber, mothersPhoneNumber, parentEmail, photo, D.name AS dorm, B.busstopName AS busstop "
                          "FROM student AS S "
                          "LEFT OUTER JOIN gender AS G ON S.genderId = G.genderId "
                          "LEFT OUTER JOIN nationality AS N ON S.nationalityId = N.nationalityId "
                          "LEFT OUTER JOIN dormitory AS D ON D.dormitoryId = S.dormitoryId "
                          "LEFT OUTER JOIN bus_stop AS B ON B.busstopId = S.busstopId "
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
    query.prepare("SELECT className, subjectName, classroomName, Teachers "
                  "FROM class_summary WHERE classId = :classId");

    query.bindValue(":classId", classId);

    if (query.exec())
    {
        if (query.next())
        {
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
    query.prepare("DELETE FROM teacher_class WHERE teacherId = :teacherId");
    query.bindValue(":teacherId", teacherId);

    if (!query.exec())
    {
        qDebug() << "Unable to delete teacher taught classes";
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
                          "mothersPhoneNumber = :mothersPhoneNumber, parentEmail = :parentEmail, photo = :photo, "
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
    query.prepare("DELETE FROM class_student WHERE studentId = :studentId");
    query.bindValue(":studentId", studentId);

    if (!query.exec())
    {
        qDebug() << "Unable to remove student class rows";
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
}

void DatabaseManager::saveClassData(const Class &c)
{
    QSqlQuery query;

    // first update the class table
    query.prepare("UPDATE class SET "
                  "className = :className,"
                  "subjectId = (SELECT subjectId FROM subject WHERE subjectName = :subjectName),"
                  "classroomId = (SELECT classroomId FROM classroom WHERE classroomName = :classroomName) "
                  "WHERE classId = :classId");
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
    query.prepare("DELETE FROM teacher_class WHERE classId = :classId");
    query.bindValue(":classId", c.classId());

    if (!query.exec())
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
    query.prepare("DELETE FROM class_student WHERE classId = :classId");
    query.bindValue(":classId", c.classId());

    if (!query.exec())
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

void DatabaseManager::removeStudent(const QString &studentId)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM student WHERE studentId = %1").arg(studentId));

    if (!query.exec())
    {
        qDebug() << "Unable to delete student: " << query.lastError().text();
    }
}

void DatabaseManager::removeTeacher(const QString &teacherId)
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM teacher WHERE teacherId = %1").arg(teacherId));

    if (!query.exec())
    {
        qDebug() << "Unable to delete teacher: " << query.lastError().text();
    }
}

void DatabaseManager::removeClass(const QString &classId)
{
    QSqlQuery query;

    // remove record from teacher_class table
    query.prepare("DELETE FROM teacher_class WHERE classId = :classId");
    query.bindValue(":classId", classId);

    if (!query.exec())
    {
        qDebug() << "Unable to delete class reference from teacher_class table";
    }

    // remove record from class_student table
    query.prepare("DELETE FROM class_student WHERE classId = :classId");
    query.bindValue(":classId", classId);

    if (!query.exec())
    {
        qDebug() << "Unable to delete class reference from class_student table";
    }

    // finally remove record from class table
    query.prepare("DELETE FROM class WHERE classId = :classId");
    query.bindValue(":classId", classId);

    if (!query.exec())
    {
        qDebug() << "classId to delete:" << classId;
        qDebug() << "Unable to delete from class table";
        qDebug() << query.lastError().text();
        return;
    }
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
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    mDatabase->setDatabaseName(path);

    // add error checking later
    mDatabase->open();

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
