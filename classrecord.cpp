#include "classrecord.h"

ClassRecord::ClassRecord()
    : mId()
    , mClass()
    , mDate()
    , mTeacher()
{

}

ClassRecord::ClassRecord(const QString &id, const QString &theClass, const QString &date, const QString &teacher)
    : mId(id)
    , mClass(theClass)
    , mDate(date)
    , mTeacher(teacher)
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

QString ClassRecord::getClass() const
{
    return mClass;
}

void ClassRecord::setClass(const QString &theClass)
{
    mClass = theClass;
}
