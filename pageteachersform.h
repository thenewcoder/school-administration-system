#ifndef PAGETEACHERSFORM_H
#define PAGETEACHERSFORM_H

#include <QWidget>

namespace Ui {
class PageTeachersForm;
}

class QSqlRelationalTableModel;

class PageTeachersForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageTeachersForm(QWidget *parent = 0);
    ~PageTeachersForm();

private slots:
    void editTeacher();
    void addTeacher();

private:
    void setupConnections();

private:
    Ui::PageTeachersForm *ui;

    QSqlRelationalTableModel *mModel;

};

#endif // PAGETEACHERSFORM_H
