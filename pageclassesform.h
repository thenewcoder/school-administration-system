#ifndef PAGECLASSESFORM_H
#define PAGECLASSESFORM_H

#include <QWidget>

namespace Ui {
class PageClassesForm;
}

class PageClassesForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageClassesForm(QWidget *parent = 0);
    ~PageClassesForm();

private:
    Ui::PageClassesForm *ui;
};

#endif // PAGECLASSESFORM_H
