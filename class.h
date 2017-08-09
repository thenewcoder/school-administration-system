#ifndef CLASS_H
#define CLASS_H

#include <QString>
#include <QStringList>

class Class
{
public:
    Class();

    QString classId() const;
    void setClassId(const QString &classId);

    QString className() const;
    void setClassname(const QString &name);

    QString subject() const;
    void setSubject(const QString &subject);

    QString classRoom() const;
    void setClassroom(const QString &room);

    QStringList teachers() const;
    void setTeachers(const QStringList &teachers);

    QStringList students() const;
    void setStudents(const QStringList &students);

private:
    QString mClassId;
    QString mClassname;
    QString mSubject;
    QString mClassroom;
    QStringList mTeachers;
    QStringList mStudents;
};

#endif // CLASS_H
