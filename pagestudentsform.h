#ifndef PAGESTUDENTSFORM_H
#define PAGESTUDENTSFORM_H

#include <QWidget>

namespace Ui {
class PageStudentsForm;
}

class QSqlTableModel;

class PageStudentsForm : public QWidget
{
    Q_OBJECT

public:
    enum FIELDS
    {
        ID,
        NAME,
        GRADE,
        GENDER,
        NATIONALITY,
        IDNUMBER,
        PHONE,
        DORM
    };

public:
    explicit PageStudentsForm(QWidget *parent = 0);
    ~PageStudentsForm();

signals:
    void notifyStudentChanged();

private:
    void setupConnections();
    void addTableHeaders();

public slots:
    void updateStudentsTable();

private slots:
    void editStudent();
    void addStudent();
    void deleteStudent();

private:
    Ui::PageStudentsForm *ui;

    QSqlTableModel *mModel;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // PAGESTUDENTSFORM_H
