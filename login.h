#ifndef LOGIN_H
#define LOGIN_H

#include <QString>

class User;

class Login
{
public:

    static bool validLogin(const QString &username, const QString &password);
    static User getUserData(const QString &username);
};

#endif // LOGIN_H
