﻿#include "personalprofileform.h"
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
}

void PersonalProfileForm::setupConnections()
{
    connect(ui->btnSave, &QPushButton::clicked, [this] () {
        User user = Login::instance().getUserData();
        user.setUsername(ui->leUsername->text());
        user.setFullName(ui->leFullName->text());
        Login::instance().updateUserData(user);
    });

    connect(ui->btnChangePassword, &QPushButton::clicked, [this] () {
        /*
         * Check that the new password isn't the same as old password
         * and that the new password equals the confirmed password
         */

        User user = Login::instance().getUserData();
        QString encryptedPassword = Login::instance().encryptString(ui->leNewPassword->text());

        if (ui->leNewPassword->text() == ui->leConfirmNewPassword->text() &&
                encryptedPassword != user.password())
        {
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
