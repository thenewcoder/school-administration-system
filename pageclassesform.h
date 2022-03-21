#ifndef PAGECLASSESFORM_H
#define PAGECLASSESFORM_H

#include <QWidget>

namespace Ui {
class PageClassesForm;
}

class QSqlTableModel;

class PageClassesForm : public QWidget
{
    Q_OBJECT

public:
    enum FIELDS
    {
        ID,
        GRADE,
        NAME,
        SUBJECT,
        ROOM,
        TEACHERS,
        ENROLLMENT
    };

public:
    explicit PageClassesForm(QWidget *parent = 0);
    ~PageClassesForm();

signals:
    void notifyClassesChanged();

public slots:
    void updateClassTable();

private:
    void setupConnections();
    void addTableHeaders();

private:
    Ui::PageClassesForm *ui;

    QSqlTableModel *mModel;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // PAGECLASSESFORM_H
