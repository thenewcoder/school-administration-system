#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QString>

class Attendance
{
public:
    Attendance();
    Attendance(const QString &student);
    Attendance(const QString &student, const int attendance_type, const QString &remarks);
    bool operator!=(const Attendance &other) const;
    ~Attendance();

    const QString &student() const;
    void setStudent(const QString &newStudent);

    int attendanceType() const;
    void setAttendanceType(int newAttendanceType);

    const QString &remarks() const;
    void setRemarks(const QString &newRemarks);

private:
    QString mStudent;
    int mAttendanceType;
    QString mRemarks;
};

#endif // ATTENDANCE_H
