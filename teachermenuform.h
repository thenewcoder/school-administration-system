#ifndef TEACHERMENUFORM_H
#define TEACHERMENUFORM_H

#include <QWidget>

namespace Ui {
class TeacherMenuForm;
}

class PageHomeForm;
class PageStudentsForm;
class PageTeachersForm;
class PageClassesForm;
class PageAttendanceForm;
class PageOtherForm;
class PageActivitiesForm;

class TeacherMenuForm : public QWidget
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
    explicit TeacherMenuForm(QWidget *parent = 0);
    ~TeacherMenuForm();

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
    Ui::TeacherMenuForm *ui;

    PageHomeForm *mPageHomeForm;
    PageStudentsForm *mPageStudentsForm;
    PageTeachersForm *mPageTeachersForm;
    PageClassesForm *mPageClassesForm;
    PageAttendanceForm *mPageAttendanceForm;
    PageOtherForm *mPageOtherForm;
    PageActivitiesForm *mPageActivitiesForm;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // TEACHERMENUFORM_H
