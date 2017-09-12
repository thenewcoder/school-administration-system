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
    explicit PageActivitiesForm(QWidget *parent = 0);
    ~PageActivitiesForm();

private:
    void setupConnections();
    void initTables();

private:
    Ui::PageActivitiesForm *ui;

    QSqlTableModel *mModelSports;
    QSqlTableModel *mModelActivities;
};

#endif // PAGEACTIVITIESFORM_H
