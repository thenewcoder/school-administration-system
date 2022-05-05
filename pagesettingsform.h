#ifndef PAGESETTINGSFORM_H
#define PAGESETTINGSFORM_H

#include <QWidget>

namespace Ui {
class PageSettingsForm;
}

class SchoolSettingsForm;
class PersonalProfileForm;
class SystemSettingsForm;
class PageHomeForm;
class UserManagerForm;

class PageSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageSettingsForm(PageHomeForm *pageHomeForm, QWidget *parent = 0);
    ~PageSettingsForm();

private:
    void setupConnections();

signals:
    void notifySchoolNameChanged(const QString &name);

private:
    Ui::PageSettingsForm *ui;

    PageHomeForm *mPageHomeForm;
    SchoolSettingsForm *mSchoolSettingsForm;
    PersonalProfileForm *mPersonalProfileForm;
    SystemSettingsForm *mSystemSettingsForm;
    UserManagerForm *mUserManagerForm;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // PAGESETTINGSFORM_H
