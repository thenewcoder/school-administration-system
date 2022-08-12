#include "teacher.h"

Teacher::Teacher()
    : mName(""), mPreferredName(""), mGender("")
    , mNationality(""), mAddress("")
    , mPhoneNumber(""), mPhoto()
{

}

Teacher::Teacher(const QString &id, const QString &name, const QString &preferredName, const QString &gender,
                 const QString &nationality, const QString &address, const QString &phoneNumber, const QByteArray &photo)
    : mId(id), mName(name), mPreferredName(preferredName), mGender(gender)
    , mNationality(nationality), mAddress(address)
    , mPhoneNumber(phoneNumber), mPhoto(photo)
{

}

Teacher::~Teacher()
{
}

Teacher::Teacher(const Teacher &other)
    : mId{other.mId}
    , mName{other.mName}
    , mPreferredName{other.mPreferredName}
    , mGender{other.mGender}
    , mNationality{other.mNationality}
    , mAddress{other.mAddress}
    , mPhoneNumber{other.mPhoneNumber}
    , mPhoto{other.mPhoto}
    , mClassesTaught{other.mClassesTaught}
{
}

Teacher &Teacher::operator=(const Teacher &other)
{
    mId = other.mId;
    mName = other.mName;
    mPreferredName = other.mPreferredName;
    mGender = other.mGender;
    mNationality = other.mNationality;
    mAddress = other.mAddress;
    mPhoneNumber = other.mPhoneNumber;
    mPhoto = other.mPhoto;
    mClassesTaught = other.mClassesTaught;

    return *this;
}

Teacher::Teacher(Teacher &&other) noexcept
    : mId{std::move(other.mId)}
    , mName{std::move(other.mName)}
    , mPreferredName{std::move(other.mPreferredName)}
    , mGender{std::move(other.mGender)}
    , mNationality{std::move(other.mNationality)}
    , mAddress{std::move(other.mAddress)}
    , mPhoneNumber{std::move(other.mPhoneNumber)}
    , mPhoto{std::move(other.mPhoto)}
    , mClassesTaught{std::move(other.mClassesTaught)}
{
}

Teacher &Teacher::operator=(Teacher &&other) noexcept
{
    if (this != &other)
    {
        mId = std::move(other.mId);
        mName = std::move(other.mName);
        mPreferredName = std::move(other.mPreferredName);
        mGender = std::move(other.mGender);
        mNationality = std::move(other.mNationality);
        mAddress = std::move(other.mAddress);
        mPhoneNumber = std::move(other.mPhoneNumber);
        mPhoto = std::move(other.mPhoto);
        mClassesTaught = std::move(other.mClassesTaught);

        other.mId = "";
        other.mName = "";
        other.mPreferredName = "";
        other.mGender = "";
        other.mNationality = "";
        other.mAddress = "";
        other.mPhoneNumber = "";
        other.mPhoto.clear();
        other.mClassesTaught.clear();
    }

    return *this;
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

QStringList Teacher::classesTaught() const
{
    return mClassesTaught;
}

void Teacher::setClassesTaught(const QStringList &classes)
{
    mClassesTaught = classes;
}

QString Teacher::preferredName() const
{
    return mPreferredName;
}

void Teacher::setPreferredName(const QString &preferredName)
{
    mPreferredName = preferredName;
}

QString Teacher::id() const
{
    return mId;
}

void Teacher::setId(const QString &id)
{
    mId = id;
}
