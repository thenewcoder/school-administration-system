#include "attendance.h"

Attendance::Attendance()
    : mStudent("")
    , mAttendanceType(-1)
    , mRemarks("")
{
}

Attendance::Attendance(const QString &student)
    : mStudent(student)
    , mAttendanceType(-1)
    , mRemarks("")
{
}

Attendance::Attendance(const QString &student, const int attendance_type, const QString &remarks)
    : mStudent(student)
    , mAttendanceType(attendance_type)
    , mRemarks(remarks)
{
}

bool Attendance::operator!=(const Attendance &other) const
{
    return (mStudent != other.mStudent ||
            mAttendanceType != other.mAttendanceType ||
            mRemarks != other.mRemarks);
}

Attendance::~Attendance()
{
}

const QString &Attendance::student() const
{
    return mStudent;
}

void Attendance::setStudent(const QString &newStudent)
{
    mStudent = newStudent;
}

int Attendance::attendanceType() const
{
    return mAttendanceType;
}

void Attendance::setAttendanceType(int newAttendanceType)
{
    mAttendanceType = newAttendanceType;
}

const QString &Attendance::remarks() const
{
    return mRemarks;
}

void Attendance::setRemarks(const QString &newRemarks)
{
    mRemarks = newRemarks;
}
