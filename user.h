#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(const QString &username, const QString &password, const QString &fullname);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    QString fullName() const;
    void setFullName(const QString &fullName);

private:
    QString mUsername;
    QString mPassword;
    QString mFullName;
};

#endif // USER_H
