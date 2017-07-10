#ifndef PAGESETTINGSFORM_H
#define PAGESETTINGSFORM_H

#include <QWidget>

namespace Ui {
class PageSettingsForm;
}

class PageSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageSettingsForm(QWidget *parent = 0);
    ~PageSettingsForm();

private:
    Ui::PageSettingsForm *ui;
};

#endif // PAGESETTINGSFORM_H
