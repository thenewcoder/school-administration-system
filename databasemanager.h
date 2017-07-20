﻿#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include <memory>
#include <QStringList>

class QSqlQuery;
class QSqlDatabase;
class Teacher;
class Student;

// temporary name
const QString DATABASE_FILENAME = "database.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    int numClasses() const;
    int numTeachers() const;
    int numStudents() const;
    QStringList nationalities() const;

    void addTeacher(const Teacher &teacher) const;
    void addStudent(const Student &student) const;

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    void createDatabase();

private:
    std::unique_ptr<QSqlDatabase> mDatabase;
};

#endif // DATABASEMANAGER_H
