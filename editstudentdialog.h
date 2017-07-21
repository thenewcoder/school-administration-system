﻿#ifndef EDITSTUDENTDIALOG_H
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

    QDate dateOfBirth() const;
    void setDateOfBirth(const QDate &date);

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

private:
    void setupConnections();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditStudentDialog *ui;
};

#endif // EDITSTUDENTDIALOG_H
