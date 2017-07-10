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

private:
    Ui::PageStudentsForm *ui;
};

#endif // PAGESTUDENTSFORM_H
