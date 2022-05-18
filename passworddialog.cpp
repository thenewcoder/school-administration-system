#include "passworddialog.h"
#include "ui_passworddialog.h"

#include "login.h"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);

    ui->lePassword->setFocus();
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

bool PasswordDialog::isAuthenticated() const
{
    return Login::instance().validLogin(Login::instance().username(), getPasswordString());
}

QString PasswordDialog::getPasswordString() const
{
    return ui->lePassword->text();
}
