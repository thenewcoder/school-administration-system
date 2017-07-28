#include "login.h"

#include "databasemanager.h"

Login &Login::instance()
{
    static Login singleton;
    return singleton;
}

QString Login::username() const
{
    return mUser.username();
}

QString Login::password() const
{
    return mUser.password();
}

QString Login::fullname() const
{
    return mUser.fullName();
}

bool Login::validLogin(const QString &username, const QString &password)
{
    // TODO: add encryption to username and password
    if (DatabaseManager::instance().validateLogin(username, password))
    {
        mUser = DatabaseManager::instance().getUser(username);
        return true;
    }
    return false;
}

Login::Login()
    : mUser()
{

}
