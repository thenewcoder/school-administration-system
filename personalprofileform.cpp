#include "personalprofileform.h"
#include "ui_personalprofileform.h"

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

void PersonalProfileForm::setupConnections()
{
    connect(ui->btnSave, &QPushButton::clicked, [this] () {

    });

    connect(ui->btnChangePassword, &QPushButton::clicked, [this] () {

    });
}
