#include "user.h"

User::User()
    : mUserId()
    , mUsername()
    , mPassword()
    , mFullName()
    , mUserType(-1)
    , mConnectedTeacher(0)
    , mLanguagePref(0)
{

}

User::User(const QString &userid, const QString &username, const QString &password,
           const QString &fullname, const int userType, const int connectedTeacher,
           const int languagePref)
    : mUserId{userid}
    , mUsername{username}
    , mPassword{password}
    , mFullName{fullname}
    , mUserType{userType}
    , mConnectedTeacher{connectedTeacher}
    , mLanguagePref{languagePref}
{
}

User::~User()
{
}

User::User(const User &other)
    : mUserId{other.mUserId}
    , mUsername{other.mUsername}
    , mPassword{other.mPassword}
    , mFullName{other.mFullName}
    , mUserType{other.mUserType}
    , mConnectedTeacher{other.mConnectedTeacher}
    , mLanguagePref{other.mLanguagePref}
{
}

User &User::operator=(const User &other)
{
    mUserId = other.mUserId;
    mUsername = other.mUsername;
    mPassword = other.mPassword;
    mFullName = other.mFullName;
    mUserType = other.mUserType;
    mConnectedTeacher = other.mConnectedTeacher;
    mLanguagePref = other.mLanguagePref;
    return *this;
}

User::User(User &&other) noexcept
    : mUserId{std::move(other.mUserId)}
    , mUsername{std::move(other.mUsername)}
    , mPassword{std::move(other.mPassword)}
    , mFullName{std::move(other.mFullName)}
    , mUserType{std::move(other.mUserType)}
    , mConnectedTeacher{std::move(other.mConnectedTeacher)}
    , mLanguagePref{std::move(other.mLanguagePref)}
{
}

User &User::operator=(User &&other) noexcept
{
    if (this != &other)
    {
        mUserId = std::move(other.mUserId);
        mUsername = std::move(other.mUsername);
        mPassword = std::move(other.mPassword);
        mFullName = std::move(other.mFullName);
        mUserType = std::move(other.mUserType);
        mConnectedTeacher = std::move(other.mConnectedTeacher);
        mLanguagePref = std::move(other.mLanguagePref);

        other.mUserId = -1;
        other.mUsername.clear();
        other.mPassword.clear();
        other.mFullName.clear();
        other.mUserType = -1;
        other.mConnectedTeacher = 0;
        other.mLanguagePref = 0;
    }
    return *this;
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

int User::connectedTeacher() const
{
    return mConnectedTeacher;
}

void User::setConnectedTeacher(int newConnectedTeacher)
{
    mConnectedTeacher = newConnectedTeacher;
}

int User::languagePreference() const
{
    return mLanguagePref;
}

void User::setLanguagePreference(int languagePref)
{
    mLanguagePref = languagePref;
}
