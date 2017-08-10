#ifndef EDITTEACHERDIALOG_H
#define EDITTEACHERDIALOG_H

#include <QDialog>

namespace Ui {
class EditTeacherDialog;
}

class Teacher;
class QStringListModel;

class EditTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTeacherDialog(QWidget *parent, const QString &teacherId = QString());
    ~EditTeacherDialog();

    void setTeacher(const Teacher &teacher);
    Teacher getTeacher() const;

    QString name() const;
    void setName(const QString &name);

    QString gender() const;
    void setGender(const QString &gender);

    QString nationality() const;
    void setNationality(const QString &nationality);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    QByteArray photo() const;
    void setPhoto(const QByteArray &photo);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void setupConnections();

private:
    Ui::EditTeacherDialog *ui;

    QStringListModel *mModelClasses;

    QString mTeacherId;
    bool mDefaultPhoto;
};

#endif // EDITTEACHERDIALOG_H
