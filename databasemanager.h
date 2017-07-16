#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include <memory>

class QSqlQuery;
class QSqlDatabase;

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

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);

private:
    std::unique_ptr<QSqlDatabase> mDatabase;
};

#endif // DATABASEMANAGER_H
