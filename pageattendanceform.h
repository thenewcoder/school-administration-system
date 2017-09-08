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
    enum FIELDS  // currently only using the ID...
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

public slots:
    void updateAttendanceTable();

private:
    Ui::PageAttendanceForm *ui;

    QSqlTableModel *mModel;
};

#endif // PAGEATTENDANCEFORM_H
