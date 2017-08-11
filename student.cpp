#include "student.h"

Student::Student()
    : mId(""), mName(""), mDateOfBirth(""), mGender("")
    , mNationality(""), mPassportNumber(""), mIDNumber("")
    , mAddress(""), mStudentPhoneNumber(""), mStudentEmail("")
    , mFathersPhoneNumber(""), mMothersPhoneNumber(""), mParentsEmail("")
    , mPhoto(), mDormitory(""), mBusstop("")
{

}

Student::Student(const QString &id, const QString &name, const QString &dateOfBirth, const QString &gender, const QString &nationality,
                 const QString &passportNumber, const QString &iDNumber, const QString &address,
                 const QString &studentPhoneNumber, const QString &studentEmail, const QString &fathersPhoneNumber,
                 const QString &mothersPhoneNumber, const QString &parentsEmail, const QByteArray &photo,
                 const QString &dormitory, const QString &busstop)
    : mId(id), mName(name), mDateOfBirth(dateOfBirth), mGender(gender)
    , mNationality(nationality), mPassportNumber(passportNumber), mIDNumber(iDNumber)
    , mAddress(address), mStudentPhoneNumber(studentPhoneNumber), mStudentEmail(studentEmail)
    , mFathersPhoneNumber(fathersPhoneNumber), mMothersPhoneNumber(mothersPhoneNumber)
    , mParentsEmail(parentsEmail), mPhoto(photo), mDormitory(dormitory), mBusstop(busstop)
{

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

QString Student::getId() const
{
    return mId;
}

void Student::setId(const QString &id)
{
    mId = id;
}
