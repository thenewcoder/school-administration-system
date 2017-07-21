#ifndef PAGESTUDENTSFORM_H
#define PAGESTUDENTSFORM_H

#include <QWidget>

namespace Ui {
class PageStudentsForm;
}

class QSqlRelationalTableModel;

class PageStudentsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageStudentsForm(QWidget *parent = 0);
    ~PageStudentsForm();

signals:
    void notifyStudentChanged();

private:
    void setupConnections();

private slots:
    void editStudent();
    void addStudent();
    void deleteStudent();

private:
    Ui::PageStudentsForm *ui;

    QSqlRelationalTableModel *mModel;
};

#endif // PAGESTUDENTSFORM_H
