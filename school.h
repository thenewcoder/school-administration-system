#ifndef SCHOOL_H
#define SCHOOL_H

#include <QString>
#include <QPixmap>

class School
{
public:
    School();
    School(const QString &name, const QString &address, const QString &phone,
           const QString &email, const QString &principal, const QByteArray &logo = QByteArray());

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

    QPixmap schoolLogoPixmap() const;
    void setSchoolLogoPixmap(const QPixmap &schoolLogoPixmap);

    QString principal() const;
    void setPrincipal(const QString &principal);

private:
    QString mSchoolName;
    QString mSchoolAddress;
    QString mSchoolPhone;
    QString mSchoolEmail;

    QByteArray mSchoolLogo;
    QPixmap mSchoolLogoPixmap;

    QString mPrincipal;

};

#endif // SCHOOL_H
