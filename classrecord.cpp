#include "classrecord.h"
#include "attendance.h"

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

ClassRecord::~ClassRecord()
{
}

ClassRecord::ClassRecord(const ClassRecord &cr)
    : mId(cr.mId)
    , mClass(cr.mClass)
    , mDate(cr.mDate)
    , mTeacher(cr.mTeacher)
    , mAttendance(cr.mAttendance)
{
}

ClassRecord::ClassRecord(ClassRecord &&cr) noexcept
    : mId(std::move(cr.mId))
    , mClass(std::move(cr.mClass))
    , mDate(std::move(cr.mDate))
    , mTeacher(std::move(cr.mTeacher))
    , mAttendance(std::move(cr.mAttendance))
{
}

ClassRecord &ClassRecord::operator=(const ClassRecord &other)
{
    mId = other.mId;
    mClass = other.mClass;
    mDate = other.mDate;
    mTeacher = other.mTeacher;
    mAttendance = other.mAttendance;
    return *this;
}

ClassRecord &ClassRecord::operator=(ClassRecord &&other) noexcept
{
    if (this != &other)
    {
        mId = std::move(other.mId);
        mClass = std::move(other.mClass);
        mDate = std::move(other.mDate);
        mTeacher = std::move(other.mTeacher);
        mAttendance = std::move(other.mAttendance);

        other.mId = -1;
        other.mClass.clear();
        other.mDate.clear();
        other.mTeacher.clear();
        mAttendance.clear();
    }
    return *this;
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

QVector<Attendance> ClassRecord::getAttendance() const
{
    return mAttendance;
}

void ClassRecord::setAttendance(const QVector<Attendance> &records)
{
    mAttendance = records;
}

void ClassRecord::addAttendanceRecord(const Attendance &attendance)
{
    mAttendance.append(attendance);
}

QString ClassRecord::getClass() const
{
    return mClass;
}

void ClassRecord::setClass(const QString &theClass)
{
    mClass = theClass;
}
