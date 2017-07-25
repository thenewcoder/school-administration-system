#ifndef SCHOOL_H
#define SCHOOL_H

#include <QString>

class School
{
public:
    School();
    School(const QString &name, const QString &address, const QString &phone,
           const QString &email, const QByteArray &logo);

    QString schoolName() const;
    void setSchoolName(const QString &schoolName);

    QString schoolAddress() const;
    void setSchoolAddress(const QString &schoolAddress);

    QString schoolPhone() const;
    void setSchoolPhone(const QString &schoolPhone);

    QString schoolEmail() const;
    void setSchoolEmail(const QString &schoolEmail);

    QByteArray schoolLogo() const;
    void setSchoolLogo(const QByteArray &schoolLogo);

private:
    QString mSchoolName;
    QString mSchoolAddress;
    QString mSchoolPhone;
    QString mSchoolEmail;

    QByteArray mSchoolLogo;

};

#endif // SCHOOL_H
