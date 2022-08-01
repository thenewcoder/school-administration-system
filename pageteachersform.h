#ifndef PAGETEACHERSFORM_H
#define PAGETEACHERSFORM_H

#include <QWidget>

namespace Ui {
class PageTeachersForm;
}

class QSqlTableModel;

class PageTeachersForm : public QWidget
{
    Q_OBJECT

public:
    enum FIELDS
    {
        ID,
        NAME,
        PREFERRED_NAME,
        GENDER,
        NATIONALITY,
        PHONE,
        CLASSES
    };

public:
    explicit PageTeachersForm(QWidget *parent = 0);
    ~PageTeachersForm();

signals:
    void notifyTeacherChanged();

public slots:
    void updateTeacherTable();

private slots:
    void editTeacher();
    void addTeacher();
    void deleteTeacher();

private:
    void setupConnections();
    void addTableHeaders();

private:
    Ui::PageTeachersForm *ui;

    QSqlTableModel *mModel;


    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // PAGETEACHERSFORM_H
