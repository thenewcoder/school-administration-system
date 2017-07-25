#include "school.h"

#include <QBuffer>

School::School()
    : mSchoolName(""), mSchoolAddress("")
    , mSchoolPhone(""), mSchoolEmail("")
    , mSchoolLogo()
    , mSchoolLogoPixmap()
{

}

School::School(const QString &name, const QString &address, const QString &phone, const QString &email, const QByteArray &logo)
    : mSchoolName(name), mSchoolAddress(address)
    , mSchoolPhone(phone), mSchoolEmail(email)
    , mSchoolLogo(logo)
    , mSchoolLogoPixmap()
{

}

QString School::schoolName() const
{
    return mSchoolName;
}

void School::setSchoolName(const QString &schoolName)
{
    mSchoolName = schoolName;
}

QString School::schoolAddress() const
{
    return mSchoolAddress;
}

void School::setSchoolAddress(const QString &schoolAddress)
{
    mSchoolAddress = schoolAddress;
}

QString School::schoolPhone() const
{
    return mSchoolPhone;
}

void School::setSchoolPhone(const QString &schoolPhone)
{
    mSchoolPhone = schoolPhone;
}

QString School::schoolEmail() const
{
    return mSchoolEmail;
}

void School::setSchoolEmail(const QString &schoolEmail)
{
    mSchoolEmail = schoolEmail;
}

QByteArray School::schoolLogo() const
{
    return mSchoolLogo;
}

void School::setSchoolLogo(const QByteArray &schoolLogo)
{
    mSchoolLogo = schoolLogo;

    // also set the pixmap
    mSchoolLogoPixmap.loadFromData(schoolLogo);
}

QPixmap School::schoolLogoPixmap() const
{
    return mSchoolLogoPixmap;
}

void School::setSchoolLogoPixmap(const QPixmap &schoolLogoPixmap)
{
    mSchoolLogoPixmap = schoolLogoPixmap;

    // also set the byte array
    QBuffer buffer(&mSchoolLogo);
    buffer.open(QIODevice::WriteOnly);
    schoolLogoPixmap.save(&buffer, "PNG");
}
