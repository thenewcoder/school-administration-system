#ifndef CLASSRECORD_H
#define CLASSRECORD_H

#include <QString>
#include <QVector>

class Attendance;

class ClassRecord
{
public:
    ClassRecord();
    ClassRecord(const QString &id, const QString &theClass, const QString &date, const QString &teacher);
    ~ClassRecord();

    ClassRecord(const ClassRecord &cr);
    ClassRecord& operator=(const ClassRecord &other);

    ClassRecord(ClassRecord &&other) noexcept;
    ClassRecord& operator=(ClassRecord &&other) noexcept;

    QString getRecordId() const;
    void setRecordId(const QString &id);

    QString getClass() const;
    void setClass(const QString &theClass);

    QString getDate() const;
    void setDate(const QString &date);

    QString getTeacher() const;
    void setTeacher(const QString &teacher);

    QVector<Attendance> getAttendance() const;
    void setAttendance(const QVector<Attendance> &records);

    void addAttendanceRecord(const Attendance& attendance);

private:
    QString mId;
    QString mClass;
    QString mDate;
    QString mTeacher;

    QVector<Attendance> mAttendance;
};

#endif // CLASSRECORD_H
