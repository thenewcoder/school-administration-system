#ifndef EDITATTENDANCEDIALOG_H
#define EDITATTENDANCEDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class EditAttendanceDialog;
}

class QStringListModel;
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

    QMap<QString, int> getAttendance() const;
    void setAttendance(const QStringList &students, const QMap<QString, int> &attendance = QMap<QString, int>());

    bool getIsEditMode() const;
    void setIsEditMode(bool isEditmode);

    void populateTeachersBox(const QString &className);

private:
    void setupConnections();

    // QDialog interface
public slots:
    virtual void accept() override;

private:
    Ui::EditAttendanceDialog *ui;

    QString mRecordId;

    QStringListModel *mModelClasses;
    QStringListModel *mModelTeachers;

    bool mIsEditMode;
};

#endif // EDITATTENDANCEDIALOG_H
