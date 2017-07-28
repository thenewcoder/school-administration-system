#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include <memory>
#include <QStringList>

class QSqlQuery;
class QSqlDatabase;
class Teacher;
class Student;
class School;
class User;

// temporary name
const QString DATABASE_FILENAME = "database.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    bool validateLogin(const QString &username, const QString &password);

    int numClasses() const;
    int numTeachers() const;
    int numStudents() const;
    QStringList nationalities() const;

    void addTeacher(const Teacher &teacher) const;
    void addStudent(const Student &student) const;

    User getUser(const QString &username);
    School getSchoolInfo() const;
    Teacher getTeacher(const QString &teacherId);
    Student getStudent(const QString &studentId);

    void saveTeacherData(const Teacher &teacher, const QString &teacherId);
    void saveStudentData(const Student &student, const QString &studentId);
    void saveSchoolData(const School &school);

    void removeStudent(const QString &studentId);
    void removeTeacher(const QString &teacherId);

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    void createDatabase();

private:
    std::unique_ptr<QSqlDatabase> mDatabase;
};

#endif // DATABASEMANAGER_H
