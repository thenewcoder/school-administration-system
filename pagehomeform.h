#ifndef PAGEHOMEFORM_H
#define PAGEHOMEFORM_H

#include <QWidget>

namespace Ui {
class PageHomeForm;
}

class PageHomeForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageHomeForm(QWidget *parent = 0);
    ~PageHomeForm();

private:
    Ui::PageHomeForm *ui;
};

#endif // PAGEHOMEFORM_H
