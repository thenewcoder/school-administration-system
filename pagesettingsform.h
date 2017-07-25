#ifndef PAGESETTINGSFORM_H
#define PAGESETTINGSFORM_H

#include <QWidget>

namespace Ui {
class PageSettingsForm;
}

class SchoolSettingsForm;

class PageSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageSettingsForm(QWidget *parent = 0);
    ~PageSettingsForm();

private:
    void setupConnections();

private:
    Ui::PageSettingsForm *ui;

    SchoolSettingsForm *mSchoolSettingsForm;
};

#endif // PAGESETTINGSFORM_H
