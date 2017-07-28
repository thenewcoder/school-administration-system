#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include "user.h"

class Login
{
public:
    static Login& instance();
    ~Login() {}

    QString username() const;
    QString password() const;
    QString fullname() const;

    bool validLogin(const QString &username, const QString &password);
    User getUserData(const QString &username);

private:
    Login();

private:
    User mUser;
};

#endif // LOGIN_H
