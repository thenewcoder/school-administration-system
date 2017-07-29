#include "personalprofileform.h"
#include "ui_personalprofileform.h"

#include "login.h"
#include "user.h"

PersonalProfileForm::PersonalProfileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalProfileForm)
{
    ui->setupUi(this);

    setupConnections();
}

PersonalProfileForm::~PersonalProfileForm()
{
    delete ui;
}

void PersonalProfileForm::setupUser()
{
    ui->leUsername->setText(Login::instance().username());
    ui->leFullName->setText(Login::instance().fullname());
    ui->lePassword->setText(Login::instance().password());
}

void PersonalProfileForm::setupConnections()
{
    connect(ui->btnSave, &QPushButton::clicked, [this] () {

    });

    connect(ui->btnChangePassword, &QPushButton::clicked, [this] () {
        /*
         * Check that the new password isn't the same as old password
         * and that the new password equals the confirmation
         */
        if (ui->leNewPassword->text() == ui->leConfirmNewPassword->text() &&
                ui->leNewPassword->text() != ui->lePassword->text())
        {
            User user = Login::instance().getUserData();
            user.setPassword(ui->leNewPassword->text());
            if (Login::instance().updateUserData(user))
            {
                // clear the line edits again
                ui->leNewPassword->setText("");
                ui->leConfirmNewPassword->setText("");
            }
        }
    });
}
