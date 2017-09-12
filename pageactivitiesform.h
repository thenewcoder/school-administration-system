#ifndef PAGEACTIVITIESFORM_H
#define PAGEACTIVITIESFORM_H

#include <QWidget>

namespace Ui {
class PageActivitiesForm;
}

class PageActivitiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageActivitiesForm(QWidget *parent = 0);
    ~PageActivitiesForm();

private:
    Ui::PageActivitiesForm *ui;
};

#endif // PAGEACTIVITIESFORM_H
