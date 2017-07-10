#ifndef ADMINMENUFORM_H
#define ADMINMENUFORM_H

#include <QWidget>

namespace Ui {
class AdminMenuForm;
}

class AdminMenuForm : public QWidget
{
    Q_OBJECT

public:
    enum MenuItems
    {
        HOME,
        SETTINGS,
        TEACHERS,
        STUDENTS
    };

public:
    explicit AdminMenuForm(QWidget *parent = 0);
    ~AdminMenuForm();

private:
    void setupConnections();

private:
    Ui::AdminMenuForm *ui;
};

#endif // ADMINMENUFORM_H
