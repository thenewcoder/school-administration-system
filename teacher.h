#ifndef TEACHER_H
#define TEACHER_H

#include <QString>

class Teacher
{
public:
    Teacher();
    Teacher(const QString &name, const QString &gender, const QString &nationality,
            const QString &address, const QString &phoneNumber, const QByteArray &photo);

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

private:
    QString mName;
    QString mGender;
    QString mNationality;
    QString mAddress;
    QString mPhoneNumber;

    QByteArray mPhoto;
};

#endif // TEACHER_H
