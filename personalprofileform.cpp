#include "personalprofileform.h"
#include "ui_personalprofileform.h"

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

void PersonalProfileForm::setUser(const User &user)
{
    ui->leUsername->setText(user.username());
    ui->leFullName->setText(user.fullName());
    ui->lePassword->setText(user.password());
}

void PersonalProfileForm::setupConnections()
{
    connect(ui->btnSave, &QPushButton::clicked, [this] () {

    });

    connect(ui->btnChangePassword, &QPushButton::clicked, [this] () {

    });
}
