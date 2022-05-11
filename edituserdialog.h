#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>

namespace Ui {
class EditUserDialog;
}

class User;

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(QWidget *parent = nullptr);
    ~EditUserDialog();

    void setUserData(User &user);
    User &getNewUserData();

private slots:
    void updateUserData();

private:
    void setupConnections();

private:
    Ui::EditUserDialog *ui;

    User *mUser;
};

#endif // EDITUSERDIALOG_H
