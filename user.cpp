#include "user.h"

User::User()
    : mUserId()
    , mUsername()
    , mPassword()
    , mFullName()
{

}

User::User(const QString &userid, const QString &username, const QString &password, const QString &fullname)
    : mUserId(userid)
    , mUsername(username)
    , mPassword(password)
    , mFullName(fullname)
{

}

QString User::username() const
{
    return mUsername;
}

void User::setUsername(const QString &username)
{
    mUsername = username;
}

QString User::password() const
{
    return mPassword;
}

void User::setPassword(const QString &password)
{
    mPassword = password;
}

QString User::fullName() const
{
    return mFullName;
}

void User::setFullName(const QString &fullName)
{
    mFullName = fullName;
}

QString User::userId() const
{
    return mUserId;
}

void User::setUserId(const QString &userId)
{
    mUserId = userId;
}
