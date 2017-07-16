#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
}

int DatabaseManager::numClasses() const
{
    QSqlQuery query(mDatabase->database());
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
    QSqlQuery query(mDatabase->database());
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
    QSqlQuery query(mDatabase->database());
    query.prepare("SELECT COUNT(studentId) FROM student");
    if (query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }
    return 0;
}

DatabaseManager::DatabaseManager(const QString &path)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    mDatabase->setDatabaseName(path);

    // add error checking later
    mDatabase->open();
}
