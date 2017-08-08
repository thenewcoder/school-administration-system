#include "class.h"


Class::Class()
    : mClassId()
    , mClassname()
    , mSubject()
    , mClassroom()
    , mTeachers()
    , mStudents()
{

}

QString Class::className() const
{
    return mClassname;
}

void Class::setClassname(const QString &name)
{
    mClassname = name;
}

QString Class::classRoom() const
{
    return mClassroom;
}

void Class::setClassroom(const QString &room)
{
    mClassroom = room;
}

QStringList Class::teachers() const
{
    return mTeachers;
}

void Class::setTeachers(const QStringList &teachers)
{
    mTeachers = teachers;
}

QStringList Class::students() const
{
    return mStudents;
}

void Class::setStudents(const QStringList &students)
{
    mStudents = students;
}

QString Class::subject() const
{
    return mSubject;
}

void Class::setSubject(const QString &subject)
{
    mSubject = subject;
}

QString Class::classId() const
{
    return mClassId;
}

void Class::setClassId(const QString &classId)
{
    mClassId = classId;
}
