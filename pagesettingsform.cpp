#include "pagesettingsform.h"
#include "ui_pagesettingsform.h"

#include "schoolsettingsform.h"
#include "personalprofileform.h"

PageSettingsForm::PageSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSettingsForm)
{
    ui->setupUi(this);

    // Add tabs to the settings tab widget
    ui->twSettingsPages->addTab(new SchoolSettingsForm(), "School Settings");
    ui->twSettingsPages->addTab(new PersonalProfileForm(), "Personal Info");
}

PageSettingsForm::~PageSettingsForm()
{
    delete ui;
}
