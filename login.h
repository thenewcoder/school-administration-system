#ifndef LOGIN_H
#define LOGIN_H

#include <QString>

class Login
{
public:

    static bool validLogin(const QString &username, const QString &password);
};

#endif // LOGIN_H
