#include "teacher.h"

Teacher::Teacher()
    : mName(""), mGender("")
    , mNationality(""), mAddress("")
    , mPhoneNumber(""), mPhoto()
{

}

Teacher::Teacher(const QString &name, const QString &gender, const QString &nationality, const QString &address, const QString &phoneNumber, const QByteArray &photo)
    : mName(name), mGender(nationality)
    , mNationality(nationality), mAddress(address)
    , mPhoneNumber(phoneNumber), mPhoto(photo)
{

}

QString Teacher::name() const
{
    return mName;
}

void Teacher::setName(const QString &name)
{
    mName = name;
}

QString Teacher::gender() const
{
    return mGender;
}

void Teacher::setGender(const QString &gender)
{
    mGender = gender;
}

QString Teacher::nationality() const
{
    return mNationality;
}

void Teacher::setNationality(const QString &nationality)
{
    mNationality = nationality;
}

QString Teacher::address() const
{
    return mAddress;
}

void Teacher::setAddress(const QString &address)
{
    mAddress = address;
}

QString Teacher::phoneNumber() const
{
    return mPhoneNumber;
}

void Teacher::setPhoneNumber(const QString &phoneNumber)
{
    mPhoneNumber = phoneNumber;
}

QByteArray Teacher::photo() const
{
    return mPhoto;
}

void Teacher::setPhoto(const QByteArray &photo)
{
    mPhoto = photo;
}
