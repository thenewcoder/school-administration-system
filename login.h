﻿#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include "user.h"

class Login
{
public:
    enum UserType
    {
        Admin = 1,
        Teacher
    };

public:
    static Login& instance();
    ~Login() {}

    QString username() const;
    QString password() const;
    QString fullname() const;

    bool validLogin(const QString &username, const QString &password);
    User getUserData();
    int getUserType() const;

    bool isUsernameTaken(const QString &name);
    bool isValidPassword(const QString &newPassword);
    bool updateUserData(const User &user);

    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setFullname(const QString &fullname);

    QString encryptString(const QString &text);
    QString generateRandomPassword();
    QString generateRandomPasswordPlainText();

private:
    Login();

private:
    User mUser;
};

#endif // LOGIN_H
