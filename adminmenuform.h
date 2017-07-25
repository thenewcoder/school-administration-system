#ifndef ADMINMENUFORM_H
#define ADMINMENUFORM_H

#include <QWidget>

namespace Ui {
class AdminMenuForm;
}

class PageHomeForm;
class PageStudentsForm;
class PageTeachersForm;

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

    void setUsername(const QString &username);

private:
    void setupConnections();

signals:
    void notifyLoggingOut();

public slots:
    void updateSchoolLogo(const QPixmap &logo);

private:
    Ui::AdminMenuForm *ui;

    PageHomeForm *mPageHomeForm;
    PageStudentsForm *mPageStudentsForm;
    PageTeachersForm *mPageTeachersForm;
};

#endif // ADMINMENUFORM_H
