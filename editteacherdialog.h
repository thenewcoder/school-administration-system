#ifndef EDITTEACHERDIALOG_H
#define EDITTEACHERDIALOG_H

#include <QDialog>
#include <teacher.h>

namespace Ui {
class EditTeacherDialog;
}

class QStringListModel;

class EditTeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTeacherDialog(QWidget *parent);
    ~EditTeacherDialog();

    void setTeacher(const Teacher &teacher);
    Teacher getTeacher() const;

    QString getId() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString preferredName() const;
    void setPreferredName(const QString &preferredName);

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

    QStringList classesTaught() const;
    void setClassesTaught(const QStringList &classes);

    void setEditMode(bool state);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void onProfileHasChanged();

private:
    void setupConnections();
    void setupDetectEditConnections();
    void toggleSaveButton(bool state);

private:
    Ui::EditTeacherDialog *ui;

    QStringListModel *mModelClasses;

    QString mTeacherId;
    bool mDefaultPhoto;

    bool mEditMode;

    Teacher mTeacher;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // EDITTEACHERDIALOG_H
