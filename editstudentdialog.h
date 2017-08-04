#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class EditStudentDialog;
}

class Student;

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStudentDialog(QWidget *parent = 0);
    ~EditStudentDialog();

    void setStudent(const Student &student);
    Student getStudent() const;

    QString name() const;
    void setName(const QString &name);

    QString dateOfBirth() const;
    void setDateOfBirth(const QString &date);

    QString gender() const;
    void setGender(const QString &gender);

    QString nationality() const;
    void setNationality(const QString &nationality);

    QString passportNumber() const;
    void setPassportNumber(const QString &number);

    QString idNumber() const;
    void setIdNumber(const QString &number);

    QString address() const;
    void setAddress(const QString &address);

    QString studentPhoneNumber() const;
    void setStudentPhoneNumber(const QString &number);

    QString studentEmail() const;
    void setStudentEmail(const QString &email);

    QString fathersPhoneNumber() const;
    void setFathersPhoneNumber(const QString &number);

    QString mothersPhoneNumber() const;
    void setMothersPhoneNumber(const QString &number);

    QString parentEmail() const;
    void setParentEmail(const QString &email);

    QByteArray photo() const;
    void setPhoto(const QByteArray &photo);

    QString dormitory() const;
    void setDormitory(const QString &dormitory);

    QString busstop() const;
    void setBusstop(const QString &busstop);

private:
    void setupConnections();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditStudentDialog *ui;

    bool mDefaultPhoto;
};

#endif // EDITSTUDENTDIALOG_H
