#include "personalprofileform.h"
#include "ui_personalprofileform.h"

#include "login.h"

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

    });
}
