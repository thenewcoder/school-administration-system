#include "login.h"

#include <QCryptographicHash>
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
    // first encrypt the password
    QString encryptedPassword = encryptString(password);

    if (DatabaseManager::instance().validateLogin(username, encryptedPassword))
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

bool Login::isUsernameTaken(const QString &name)
{
    return DatabaseManager::instance().isUsernameTaken(name);
}

bool Login::isValidPassword(const QString &newPassword)
{
    // validate the password. 6 - 16 characters and not same as old password
    if ((newPassword.length() >= 6 && newPassword.length() <= 16) &&
            encryptString(newPassword) != password())
        return true;
    return false;
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

QString Login::encryptString(const QString &text)
{
    QCryptographicHash c(QCryptographicHash::Sha256);
    c.addData(text.toStdString().c_str(), text.length());
    QString result = QString::fromStdString(c.result().toBase64().toStdString());
    return result;
}
