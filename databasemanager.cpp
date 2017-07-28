﻿#include "databasemanager.h"

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
        return list;
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
}

void DatabaseManager::addStudent(const Student &student) const
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO student "
                          "('name', 'dateOfBirth', genderId, nationalityId, "
                          "'passportNumber', 'IDNumber', 'address', "
                          "'studentPhoneNumber', 'studentEmail', 'fathersPhoneNumber', "
                          "'mothersPhoneNumber', 'parentEmail', 'photo') "
                          "VALUES(:name, :dateOfBirth, "
                          "(SELECT genderId FROM gender WHERE type = :gender), "
                          "(SELECT nationalityId FROM nationality WHERE country = :nationality), "
                          ":passportNumber, :IDNumber, :address, :studentPhoneNumber, :studentEmail, "
                          ":fathersPhoneNumber, :mothersPhoneNumber, :parentEmail, :photo)"));

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

    if (!query.exec())
    {
        qDebug() << "Unable to add a new student";
        qDebug() << query.lastError().text();
    }
}

User DatabaseManager::getUser(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT password, fullname FROM user WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec())
    {
        query.next();
        return User(username,
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
    query.prepare(QString("SELECT name, dateOfBirth, type, country, passportNumber, "
                          "IDNumber, address, studentPhoneNumber, studentEmail, "
                          "fathersPhoneNumber, mothersPhoneNumber, parentEmail, photo FROM student AS S "
                          "JOIN gender AS G ON S.genderId = G.genderId "
                          "JOIN nationality AS N ON S.nationalityId = N.nationalityId "
                          "WHERE studentId = %1").arg(studentId));
    if (query.exec())
    {
        while (query.next())
        {
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
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return student;
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
                          "mothersPhoneNumber = :mothersPhoneNumber, parentEmail = :parentEmail, photo = :photo "
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

    if (!query.exec())
    {
        qDebug() << "Unable to update student data";
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
}
