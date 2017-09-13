#ifndef PAGEACTIVITIESFORM_H
#define PAGEACTIVITIESFORM_H

#include <QWidget>

namespace Ui {
class PageActivitiesForm;
}

class QSqlTableModel;

class PageActivitiesForm : public QWidget
{
    Q_OBJECT

public:
    enum FIELDS
    {
        ID,
        CODE,
        NAME,
        TEACHER,
        LIMIT
    };

public:
    explicit PageActivitiesForm(QWidget *parent = 0);
    ~PageActivitiesForm();

private:
    void setupConnections();
    void initTables();

    void setupRefreshButtons();
    void setupAddButtons();
    void setupEditButtons();
    void setupDeleteButtons();

private slots:
    void updateSportsTable();
    void updateAfterSchoolTable();

private:
    Ui::PageActivitiesForm *ui;

    QSqlTableModel *mModelSports;
    QSqlTableModel *mModelActivities;
};

#endif // PAGEACTIVITIESFORM_H
