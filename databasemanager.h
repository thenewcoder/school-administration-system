#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QStringList>
#include <memory>

class QSqlQuery;
class QSqlDatabase;
class Teacher;
class Student;
class School;
class User;
class Class;
class ClassRecord;
class Activity;
class Attendance;

// temporary name
static const QString DATABASE_FILENAME = "database.db";

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    bool validateLogin(const QString &username, const QString &password);
    bool isUsernameTaken(const QString &name);

    int numClasses() const;
    int numTeachers() const;
    int numStudents() const;

    QStringList users() const;
    QStringList nationalities() const;
    QStringList dormitories() const;
    QStringList busstops() const;
    QStringList subjects() const;
    QStringList classrooms() const;
    QStringList teachers() const;
    QStringList students() const;
    QStringList classes() const;
    QStringList grades() const;
    QVector<Attendance> studentsOfClass(const QString &className);
    QStringList teachersOfClass(const QString &className);

    void addTeacher(const Teacher &teacher) const;
    void addStudent(const Student &student) const;
    void addClass(const Class &c) const;
    void addClassoom(const QString &name, const QString &comment);
    void addDormitory(const QString &name, const QString &comment);
    void addBusstop(const QString &name, const QString &comment);
    void addGrade(const QString &name);
    void addSubject(const QString &name);
    void addUser(const QString &username, const QString &password, const QString &fullname,
                 const int userTypeId, const int connectedTeacherId=0);
    void addUser(const User &user);
    void addClassRecord(const ClassRecord &record);
    void addActivity(const Activity &activity);

    User getUser(const QString &username);
    School getSchoolInfo() const;
    Teacher getTeacher(const QString &teacherId);
    int getTeacherId(const QString &teacherName);
    QString getTeacherName(const int teacherId);
    Student getStudent(const QString &studentId);
    Class getClass(const QString &classId);
    ClassRecord getClassRecord(const QString &recordId);
    QVector<Attendance> attendanceOfClass(const QString &className);
    Activity getActivity(const QString &activityId);

    void saveTeacherData(const Teacher &teacher, const QString &teacherId);
    void saveStudentData(const Student &student, const QString &studentId);
    void saveSchoolData(const School &school);
    void saveClassData(const Class &c);
    void saveClassRecord(const ClassRecord &record);
    void saveActivityData(const Activity &activity);

    bool updateUserData(const User &user);
    bool updateUserDataInfo(const User &user);
    bool updateClassroom(const QString &id, const QString &name, const QString &comment);
    bool updateDormitory(const QString &id, const QString &name, const QString &comment);
    bool updateBusstop(const QString &id, const QString &name, const QString &comment);
    bool updateGrade(const QString &oldName, const QString &newName);
    bool updateSubject(const QString &oldName, const QString &newName);

    bool removeStudent(const QString &studentId);
    bool removeTeacher(const QString &teacherId);
    bool removeClass(const QString &classId);
    bool removeGrade(const QString &grade);
    bool removeSubject(const QString &subject);
    bool removeTableRows(const QString &table, const QString &col, const QString &id);
    bool removeClassRecord(const QString &recordId);
    bool removeActivity(const QString &activityId);
    bool clearColumnEntry(const QString &table, const QString &col, const QString &id);

    bool removeClassroom(const QString &roomId);
    bool removeBusstop(const QString &busstopId);
    bool removeDormitory(const QString &dormId);

    QStringList classesTaken(const QString &id);
    QStringList classesTaught(const QString &id);

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    void createDatabase();

private:
    std::unique_ptr<QSqlDatabase> mDatabase;
};

#endif // DATABASEMANAGER_H
