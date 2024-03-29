﻿#ifndef EDITATTENDANCEDIALOG_H
#define EDITATTENDANCEDIALOG_H

#include <QDialog>
#include <QMap>

#include "classrecord.h"


namespace Ui {
class EditAttendanceDialog;
}

class QStringListModel;

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
    explicit EditAttendanceDialog(QWidget *parent = 0, bool isEditMode = false);
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

    void populateTeachersBox(const QString &className);

private:
    void setupConnections();
    void setupDetectEditConnections();
    void toggleOKButton(bool state);
    bool attendanceRecordsAreSame(const QVector<Attendance>& first, const QVector<Attendance>& second) const;

public slots:
    void onProfileHasChanged();

private:
    Ui::EditAttendanceDialog *ui;

    QStringListModel *mModelClasses;
    QStringListModel *mModelTeachers;

    QString mRecordId;
    ClassRecord mRecord;

    bool mEditMode;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // EDITATTENDANCEDIALOG_H
