#ifndef PAGEOTHERFORM_H
#define PAGEOTHERFORM_H

#include <QWidget>

namespace Ui {
class PageOtherForm;
}

class QSqlTableModel;
class QStringListModel;

class PageOtherForm : public QWidget
{
    Q_OBJECT

public:
    enum FIELDS
    {
        ID,
        NAME,
        COMMENT
    };

public:
    explicit PageOtherForm(QWidget *parent = 0);
    ~PageOtherForm();

signals:
    void notifyDormsChanged();
    void notifyClassroomsChanged();
    void notifySubjectsChanged();
    void notifyGradesChanged();

private:
    void setupConnections();
    void setupAddButtons();
    void setupEditButtons();
    void setupDeleteButtons();
    void setupViews();

private:
    Ui::PageOtherForm *ui;

    QSqlTableModel *mModelClassrooms;
    QSqlTableModel *mModelDormitories;
    QSqlTableModel *mModelBusStops;
    QStringListModel *mModelGrades;
    QStringListModel *mModelSubjects;
};

#endif // PAGEOTHERFORM_H
