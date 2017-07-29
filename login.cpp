﻿#include "login.h"

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

User Login::getUserData()
{
    return mUser;
}

bool Login::updateUserData(const User &user)
{
    if (DatabaseManager::instance().updateUserData(user))
    {
        setUsername(user.username());
        setPassword(user.password());
        setFullname(user.fullName());
        return true;
    }
    return false;
}

Login::Login()
    : mUser()
{

}

void Login::setUsername(const QString &username)
{
    mUser.setUsername(username);
}

void Login::setPassword(const QString &password)
{
    mUser.setPassword(password);
}

void Login::setFullname(const QString &fullname)
{
    mUser.setFullName(fullname);
}
