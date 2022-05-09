#include "user.h"

User::User()
    : mUserId()
    , mUsername()
    , mPassword()
    , mFullName()
    , mUserType(-1)
    , mConnectedUser(0)
{

}

User::User(const QString &userid, const QString &username, const QString &password,
           const QString &fullname, const int userType, const int connectedUser)
    : mUserId(userid)
    , mUsername(username)
    , mPassword(password)
    , mFullName(fullname)
    , mUserType(userType)
    , mConnectedUser(connectedUser)
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

int User::userType() const
{
    return mUserType;
}

void User::setUserType(int newUserType)
{
    mUserType = newUserType;
}

int User::connectedUser() const
{
    return mConnectedUser;
}

void User::setConnectedUser(int newConnectedUser)
{
    mConnectedUser = newConnectedUser;
}
