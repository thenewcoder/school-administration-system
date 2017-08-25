#ifndef EDITATTENDANCEDIALOG_H
#define EDITATTENDANCEDIALOG_H

#include <QDialog>

namespace Ui {
class EditAttendanceDialog;
}

class QStringListModel;
class ClassRecord;

class EditAttendanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAttendanceDialog(QWidget *parent = 0);
    ~EditAttendanceDialog();

    QString getClass() const;
    void setClass(const QString &theClass);

    QString getDate() const;
    void setDate(const QString &date);

    QString getTeacher() const;
    void setTeacher(const QString &teacher);

    ClassRecord getClassRecord() const;
    void setClassRecord(const ClassRecord &record);

private:
    Ui::EditAttendanceDialog *ui;

    QStringListModel *mModelClasses;
    QStringListModel *mModelTeachers;
};

#endif // EDITATTENDANCEDIALOG_H
