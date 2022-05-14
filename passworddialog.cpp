#include "passworddialog.h"
#include "ui_passworddialog.h"

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

QString PasswordDialog::getPasswordString() const
{
    return ui->lePassword->text();
}
