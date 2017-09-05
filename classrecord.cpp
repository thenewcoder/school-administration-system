#include "classrecord.h"

ClassRecord::ClassRecord()
    : mId()
    , mClass()
    , mDate()
    , mTeacher()
    , mAttendance()
{

}

ClassRecord::ClassRecord(const QString &id, const QString &theClass, const QString &date, const QString &teacher)
    : mId(id)
    , mClass(theClass)
    , mDate(date)
    , mTeacher(teacher)
    , mAttendance()
{

}

QString ClassRecord::getRecordId() const
{
    return mId;
}

void ClassRecord::setRecordId(const QString &id)
{
    mId = id;
}

QString ClassRecord::getDate() const
{
    return mDate;
}

void ClassRecord::setDate(const QString &date)
{
    mDate = date;
}

QString ClassRecord::getTeacher() const
{
    return mTeacher;
}

void ClassRecord::setTeacher(const QString &teacher)
{
    mTeacher = teacher;
}

QMap<QString, int> ClassRecord::getAttendance() const
{
    return mAttendance;
}

void ClassRecord::setAttendance(const QMap<QString, int> &attendance)
{
    mAttendance = attendance;
}

void ClassRecord::addAttendanceRecord(const QString &name, const int status)
{
    mAttendance.insert(name, status);
}

QString ClassRecord::getClass() const
{
    return mClass;
}

void ClassRecord::setClass(const QString &theClass)
{
    mClass = theClass;
}
