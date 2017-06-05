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
    explicit AdminMenuForm(QWidget *parent = 0);
    ~AdminMenuForm();

private:
    Ui::AdminMenuForm *ui;
};

#endif // ADMINMENUFORM_H
