#ifndef EDITATTENDANCEDIALOG_H
#define EDITATTENDANCEDIALOG_H

#include <QDialog>

namespace Ui {
class EditAttendanceDialog;
}

class QStringListModel;
class QSqlTableModel;
class ClassRecord;

class EditAttendanceDialog : public QDialog
{
    Q_OBJECT

public:
    enum FIELDS
    {
        CLASS,
        STUDENT,
        STATUS
    };

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

    QString getRecordId() const;
    void setRecordId(const QString &recordId);

private:
    void setupConnections();

private:
    Ui::EditAttendanceDialog *ui;

    QString mRecordId;

    QStringListModel *mModelClasses;
    QStringListModel *mModelTeachers;
    QSqlTableModel *mModelAttendance;
};

#endif // EDITATTENDANCEDIALOG_H
