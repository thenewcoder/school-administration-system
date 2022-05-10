#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(const QString &userid, const QString &username, const QString &password,
         const QString &fullname, const int userType = -1, const int connectedTeacher = 0);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    QString fullName() const;
    void setFullName(const QString &fullName);

    QString userId() const;
    void setUserId(const QString &userId);

    int userType() const;
    void setUserType(int newUserType);

    int connectedTeacher() const;
    void setConnectedTeacher(int newConnectedTeacher);

private:
    QString mUserId;
    QString mUsername;
    QString mPassword;
    QString mFullName;
    int mUserType;
    int mConnectedTeacher;
};

#endif // USER_H
