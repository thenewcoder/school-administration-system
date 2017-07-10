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

private:
    Ui::PageTeachersForm *ui;
};

#endif // PAGETEACHERSFORM_H
