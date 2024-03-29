﻿#ifndef TEACHER_H
#define TEACHER_H

#include <QString>
#include <QStringList>

class Teacher
{
public:
    Teacher();
    Teacher(const QString &id, const QString &name, const QString &preferredName, const QString &gender, const QString &nationality,
            const QString &address, const QString &phoneNumber, const QByteArray &photo);
    ~Teacher();

    Teacher(const Teacher &other);
    Teacher& operator=(const Teacher &other);

    Teacher(Teacher &&other) noexcept;
    Teacher& operator=(Teacher &&other) noexcept;

    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString gender() const;
    void setGender(const QString &gender);

    QString nationality() const;
    void setNationality(const QString &nationality);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    QByteArray photo() const;
    void setPhoto(const QByteArray &photo);

    QStringList classesTaught() const;
    void setClassesTaught(const QStringList &classes);

    QString preferredName() const;
    void setPreferredName(const QString &preferredName);

private:
    QString mId;
    QString mName;
    QString mPreferredName;
    QString mGender;
    QString mNationality;
    QString mAddress;
    QString mPhoneNumber;

    QByteArray mPhoto;

    QStringList mClassesTaught;
};

#endif // TEACHER_H
