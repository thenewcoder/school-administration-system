﻿#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    Student();
    Student(const QString &name, const QString &dateOfBirth, const QString &gender, const QString &nationality,
            const QString &passportNumber, const QString &iDNumber, const QString &address,
            const QString &studentPhoneNumber, const QString &studentEmail, const QString &fathersPhoneNumber,
            const QString &mothersPhoneNumber, const QString &parentsEmail, const QByteArray &photo);

    QString name() const;
    void setName(const QString &name);

    QString dateOfBirth() const;
    void setDateOfBirth(const QString &dateOfBirth);

    QString gender() const;
    void setGender(const QString &gender);

    QString nationality() const;
    void setNationality(const QString &nationality);

    QString passportNumber() const;
    void setPassportNumber(const QString &passportNumber);

    QString iDNumber() const;
    void setIDNumber(const QString &iDNumber);

    QString address() const;
    void setAddress(const QString &address);

    QString studentPhoneNumber() const;
    void setStudentPhoneNumber(const QString &studentPhoneNumber);

    QString studentEmail() const;
    void setStudentEmail(const QString &studentEmail);

    QString fathersPhoneNumber() const;
    void setFathersPhoneNumber(const QString &fathersPhoneNumber);

    QString mothersPhoneNumber() const;
    void setMothersPhoneNumber(const QString &mothersPhoneNumber);

    QString parentsEmail() const;
    void setParentsEmail(const QString &parentsEmail);

    QByteArray photo() const;
    void setPhoto(const QByteArray &photo);

private:
    QString mName;
    QString mDateOfBirth;
    QString mGender;
    QString mNationality;
    QString mPassportNumber;
    QString mIDNumber;
    QString mAddress;
    QString mStudentPhoneNumber;
    QString mStudentEmail;
    QString mFathersPhoneNumber;
    QString mMothersPhoneNumber;
    QString mParentsEmail;

    QByteArray mPhoto;
};

#endif // STUDENT_H