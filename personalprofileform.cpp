#include "personalprofileform.h"
#include "ui_personalprofileform.h"

PersonalProfileForm::PersonalProfileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalProfileForm)
{
    ui->setupUi(this);
}

PersonalProfileForm::~PersonalProfileForm()
{
    delete ui;
}
