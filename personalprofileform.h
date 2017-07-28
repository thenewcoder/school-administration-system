#ifndef PERSONALPROFILEFORM_H
#define PERSONALPROFILEFORM_H

#include <QWidget>

namespace Ui {
class PersonalProfileForm;
}

class PersonalProfileForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalProfileForm(QWidget *parent = 0);
    ~PersonalProfileForm();

public slots:
    void setupUser();

private:
    void setupConnections();

private:
    Ui::PersonalProfileForm *ui;
};

#endif // PERSONALPROFILEFORM_H
