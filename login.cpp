#include "login.h"
#include "user.h"

#include "databasemanager.h"

bool Login::validLogin(const QString &username, const QString &password)
{
    // TODO: add encryption to username and password
    return DatabaseManager::instance().validateLogin(username, password);
}

User Login::getUserData(const QString &username)
{
    return DatabaseManager::instance().getUser(username);
}
