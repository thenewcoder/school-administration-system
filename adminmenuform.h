#ifndef ADMINMENUFORM_H
#define ADMINMENUFORM_H

#include <QWidget>

namespace Ui {
class AdminMenuForm;
}

class PageHomeForm;
class PageStudentsForm;
class PageTeachersForm;
class PageClassesForm;
class PageAttendanceForm;
class PageOtherForm;
class PageActivitiesForm;

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
    void setWelcomeMessage(const QString &name);

signals:
    void notifyLoggingOut();
    void notifyUserLogon();

public slots:
    void updateSchoolLogo(const QPixmap &logo);
    void handleUserLogin();
    void onFullnameChanged(const QString &name);

private:
    Ui::AdminMenuForm *ui;

    PageHomeForm *mPageHomeForm;
    PageStudentsForm *mPageStudentsForm;
    PageTeachersForm *mPageTeachersForm;
    PageClassesForm *mPageClassesForm;
    PageAttendanceForm *mPageAttendanceForm;
    PageOtherForm *mPageOtherForm;
    PageActivitiesForm *mPageActivitiesForm;
};

#endif // ADMINMENUFORM_H
