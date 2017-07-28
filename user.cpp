#include "user.h"

User::User()
    : mUsername()
    , mPassword()
    , mFullName()
{

}

User::User(const QString &username, const QString &password, const QString &fullname)
    : mUsername(username)
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
