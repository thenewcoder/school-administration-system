#ifndef USERMANAGERFORM_H
#define USERMANAGERFORM_H

#include <QWidget>

namespace Ui {
class UserManagerForm;
}

class QSqlTableModel;

class UserManagerForm : public QWidget
{
    Q_OBJECT

    enum FIELDS
    {
        ID,
        USERNAME,
        //PASSWORD,
        FULLNAME,
        USERTYPE,
        CONNECTED
    };

public:
    explicit UserManagerForm(QWidget *parent = nullptr);
    ~UserManagerForm();

private:
    void addTableHeaders();
    void setupConnections();

private:
    Ui::UserManagerForm *ui;

    QSqlTableModel* mModel;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // USERMANAGERFORM_H
