#ifndef PAGESTUDENTSFORM_H
#define PAGESTUDENTSFORM_H

#include <QWidget>

namespace Ui {
class PageStudentsForm;
}

class PageStudentsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageStudentsForm(QWidget *parent = 0);
    ~PageStudentsForm();

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
    Ui::PageStudentsForm *ui;
};

#endif // PAGESTUDENTSFORM_H
