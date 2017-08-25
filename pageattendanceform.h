#ifndef PAGEATTENDANCEFORM_H
#define PAGEATTENDANCEFORM_H

#include <QWidget>

namespace Ui {
class PageAttendanceForm;
}

class QSqlTableModel;

class PageAttendanceForm : public QWidget
{
    Q_OBJECT

public:
    enum FIELDS
    {
        ID,
        DATE,
        CLASS,
        TEACHER,
        NSTUDENT
    };

public:
    explicit PageAttendanceForm(QWidget *parent = 0);
    ~PageAttendanceForm();

private:
    void setupConnections();

private:
    Ui::PageAttendanceForm *ui;

    QSqlTableModel *mModel;
};

#endif // PAGEATTENDANCEFORM_H
