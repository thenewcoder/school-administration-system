#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr);
    ~PasswordDialog();

    bool isAuthenticated() const;
    QString getPasswordString() const;

private:
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
