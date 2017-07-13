#ifndef PAGETEACHERSFORM_H
#define PAGETEACHERSFORM_H

#include <QWidget>

namespace Ui {
class PageTeachersForm;
}

class PageTeachersForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageTeachersForm(QWidget *parent = 0);
    ~PageTeachersForm();

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

private:
    Ui::PageTeachersForm *ui;

};

#endif // PAGETEACHERSFORM_H
