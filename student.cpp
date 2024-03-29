﻿#include "student.h"

Student::Student()
    : mId(""), mName(""), mNickName(""), mDateOfBirth(""), mGender("")
    , mNationality(""), mGrade(""), mPassportNumber(""), mIDNumber("")
    , mAddress(""), mStudentPhoneNumber(""), mStudentEmail("")
    , mFathersPhoneNumber(""), mMothersPhoneNumber(""), mParentsEmail("")
    , mPhoto(), mDormitory(""), mBusstop("")
{

}

Student::Student(const QString &id, const QString &name, const QString &nickName, const QString &dateOfBirth, const QString &gender,
                 const QString &nationality, const QString &grade, const QString &passportNumber, const QString &iDNumber,
                 const QString &address, const QString &studentPhoneNumber, const QString &studentEmail,
                 const QString &fathersPhoneNumber, const QString &mothersPhoneNumber, const QString &parentsEmail,
                 const QByteArray &photo, const QString &dormitory, const QString &busstop)
    : mId(id), mName(name), mNickName(nickName), mDateOfBirth(dateOfBirth), mGender(gender)
    , mNationality(nationality), mGrade(grade), mPassportNumber(passportNumber), mIDNumber(iDNumber)
    , mAddress(address), mStudentPhoneNumber(studentPhoneNumber), mStudentEmail(studentEmail)
    , mFathersPhoneNumber(fathersPhoneNumber), mMothersPhoneNumber(mothersPhoneNumber)
    , mParentsEmail(parentsEmail), mPhoto(photo), mDormitory(dormitory), mBusstop(busstop)
{

}

Student::~Student()
{
}

Student::Student(const Student &other)
    : mId{other.mId}
    , mName{other.mName}
    , mNickName{other.mNickName}
    , mDateOfBirth{other.mDateOfBirth}
    , mGender{other.mGender}
    , mNationality{other.mNationality}
    , mGrade{other.mGrade}
    , mPassportNumber{other.mPassportNumber}
    , mIDNumber{other.mIDNumber}
    , mAddress{other.mAddress}
    , mStudentPhoneNumber{other.mStudentPhoneNumber}
    , mStudentEmail{other.mStudentEmail}
    , mFathersPhoneNumber{other.mFathersPhoneNumber}
    , mMothersPhoneNumber{other.mMothersPhoneNumber}
    , mParentsEmail{other.mParentsEmail}
    , mPhoto{other.mPhoto}
    , mDormitory{other.mDormitory}
    , mBusstop{other.mBusstop}
    , mClassesTaken{other.mClassesTaken}
{
}

Student &Student::operator=(const Student &other)
{
    mId = other.mId;
    mName = other.mName;
    mNickName = other.mNickName;
    mDateOfBirth = other.mDateOfBirth;
    mGender = other.mGender;
    mNationality = other.mNationality;
    mGrade = other.mGrade;
    mPassportNumber = other.mPassportNumber;
    mIDNumber = other.mIDNumber;
    mAddress = other.mAddress;
    mStudentPhoneNumber = other.mStudentPhoneNumber;
    mStudentEmail = other.mStudentEmail;
    mFathersPhoneNumber = other.mFathersPhoneNumber;
    mMothersPhoneNumber = other.mMothersPhoneNumber;
    mParentsEmail = other.mParentsEmail;
    mPhoto = other.mPhoto;
    mDormitory = other.mDormitory;
    mBusstop = other.mBusstop;
    mClassesTaken = other.mClassesTaken;

    return *this;
}

Student::Student(Student &&other) noexcept
    : mId{std::move(other.mId)}
    , mName{std::move(other.mName)}
    , mNickName{std::move(other.mNickName)}
    , mDateOfBirth{std::move(other.mDateOfBirth)}
    , mGender{std::move(other.mGender)}
    , mNationality{std::move(other.mNationality)}
    , mGrade{std::move(other.mGrade)}
    , mPassportNumber{std::move(other.mPassportNumber)}
    , mIDNumber{std::move(other.mIDNumber)}
    , mAddress{std::move(other.mAddress)}
    , mStudentPhoneNumber{std::move(other.mStudentPhoneNumber)}
    , mStudentEmail{std::move(other.mStudentEmail)}
    , mFathersPhoneNumber{std::move(other.mFathersPhoneNumber)}
    , mMothersPhoneNumber{std::move(other.mMothersPhoneNumber)}
    , mParentsEmail{std::move(other.mParentsEmail)}
    , mPhoto{std::move(other.mPhoto)}
    , mDormitory{std::move(other.mDormitory)}
    , mBusstop{std::move(other.mBusstop)}
    , mClassesTaken{std::move(other.mClassesTaken)}
{
}

Student &Student::operator=(Student &&other) noexcept
{
    if (this != &other)
    {
        mId = std::move(other.mId);
        mName = std::move(other.mName);
        mNickName = std::move(other.mNickName);
        mDateOfBirth = std::move(other.mDateOfBirth);
        mGender = std::move(other.mGender);
        mNationality = std::move(other.mNationality);
        mGrade = std::move(other.mGrade);
        mPassportNumber = std::move(other.mPassportNumber);
        mIDNumber = std::move(other.mIDNumber);
        mAddress = std::move(other.mAddress);
        mStudentPhoneNumber = std::move(other.mStudentPhoneNumber);
        mStudentEmail = std::move(other.mStudentEmail);
        mFathersPhoneNumber = std::move(other.mFathersPhoneNumber);
        mMothersPhoneNumber = std::move(other.mMothersPhoneNumber);
        mParentsEmail = std::move(other.mParentsEmail);
        mPhoto = std::move(other.mPhoto);
        mDormitory = std::move(other.mDormitory);
        mBusstop = std::move(other.mBusstop);
        mClassesTaken = std::move(other.mClassesTaken);

        other.mId = "";
        other.mName = "";
        other.mNickName = "";
        other.mDateOfBirth = "";
        other.mGender = "";
        other.mNationality = "";
        other.mGrade = "";
        other.mPassportNumber = "";
        other.mIDNumber = "";
        other.mAddress = "";
        other.mStudentPhoneNumber = "";
        other.mStudentEmail = "";
        other.mFathersPhoneNumber = "";
        other.mMothersPhoneNumber = "";
        other.mParentsEmail = "";
        other.mPhoto.clear();
        other.mDormitory = "";
        other.mBusstop = "";
        other.mClassesTaken.clear();
    }

    return *this;
}

QString Student::name() const
{
    return mName;
}

void Student::setName(const QString &name)
{
    mName = name;
}

QString Student::dateOfBirth() const
{
    return mDateOfBirth;
}

void Student::setDateOfBirth(const QString &dateOfBirth)
{
    mDateOfBirth = dateOfBirth;
}

QString Student::gender() const
{
    return mGender;
}

void Student::setGender(const QString &gender)
{
    mGender = gender;
}

QString Student::nationality() const
{
    return mNationality;
}

void Student::setNationality(const QString &nationality)
{
    mNationality = nationality;
}

QString Student::passportNumber() const
{
    return mPassportNumber;
}

void Student::setPassportNumber(const QString &passportNumber)
{
    mPassportNumber = passportNumber;
}

QString Student::iDNumber() const
{
    return mIDNumber;
}

void Student::setIDNumber(const QString &iDNumber)
{
    mIDNumber = iDNumber;
}

QString Student::address() const
{
    return mAddress;
}

void Student::setAddress(const QString &address)
{
    mAddress = address;
}

QString Student::studentPhoneNumber() const
{
    return mStudentPhoneNumber;
}

void Student::setStudentPhoneNumber(const QString &studentPhoneNumber)
{
    mStudentPhoneNumber = studentPhoneNumber;
}

QString Student::studentEmail() const
{
    return mStudentEmail;
}

void Student::setStudentEmail(const QString &studentEmail)
{
    mStudentEmail = studentEmail;
}

QString Student::fathersPhoneNumber() const
{
    return mFathersPhoneNumber;
}

void Student::setFathersPhoneNumber(const QString &fathersPhoneNumber)
{
    mFathersPhoneNumber = fathersPhoneNumber;
}

QString Student::mothersPhoneNumber() const
{
    return mMothersPhoneNumber;
}

void Student::setMothersPhoneNumber(const QString &mothersPhoneNumber)
{
    mMothersPhoneNumber = mothersPhoneNumber;
}

QString Student::parentsEmail() const
{
    return mParentsEmail;
}

void Student::setParentsEmail(const QString &parentsEmail)
{
    mParentsEmail = parentsEmail;
}

QByteArray Student::photo() const
{
    return mPhoto;
}

void Student::setPhoto(const QByteArray &photo)
{
    mPhoto = photo;
}

QString Student::dormitory() const
{
    return mDormitory;
}

void Student::setDormitory(const QString &dormitory)
{
    mDormitory = dormitory;
}

QString Student::busstop() const
{
    return mBusstop;
}

void Student::setBusstop(const QString &busstop)
{
    mBusstop = busstop;
}

QStringList Student::getClassesTaken() const
{
    return mClassesTaken;
}

void Student::setClassesTaken(const QStringList &classesTaken)
{
    mClassesTaken = classesTaken;
}

QString Student::getGrade() const
{
    return mGrade;
}

void Student::setGrade(const QString &grade)
{
    mGrade = grade;
}

QString Student::nickName() const
{
    return mNickName;
}

void Student::setNickName(const QString &nickName)
{
    mNickName = nickName;
}

QString Student::getId() const
{
    return mId;
}

void Student::setId(const QString &id)
{
    mId = id;
}
