#ifndef CLASSRECORD_H
#define CLASSRECORD_H

#include <QString>
#include <QMap>

class ClassRecord
{
public:
    ClassRecord();
    ClassRecord(const QString &id, const QString &theClass, const QString &date, const QString &teacher);

    QString getRecordId() const;
    void setRecordId(const QString &id);

    QString getClass() const;
    void setClass(const QString &theClass);

    QString getDate() const;
    void setDate(const QString &date);

    QString getTeacher() const;
    void setTeacher(const QString &teacher);

    QMap<QString, int> getAttendance() const;
    void setAttendance(const QMap<QString, int> &attendance);

    void addAttendanceRecord(const QString &name, const int status);

private:
    QString mId;
    QString mClass;
    QString mDate;
    QString mTeacher;

    QMap<QString, int> mAttendance;
};

#endif // CLASSRECORD_H
