#include "pagesettingsform.h"
#include "ui_pagesettingsform.h"

#include "schoolsettingsform.h"
#include "personalprofileform.h"
#include "adminmenuform.h"

PageSettingsForm::PageSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSettingsForm),
    mSchoolSettingsForm(new SchoolSettingsForm(this))
{
    ui->setupUi(this);

    // Add tabs to the settings tab widget
    ui->twSettingsPages->addTab(mSchoolSettingsForm, "School Settings");
    ui->twSettingsPages->addTab(new PersonalProfileForm(), "Personal Info");

    setupConnections();

    mSchoolSettingsForm->loadDatabaseSettings();
}

PageSettingsForm::~PageSettingsForm()
{
    delete ui;
}

void PageSettingsForm::setupConnections()
{
    // update the school logo when the settings logo has been changed
    connect(mSchoolSettingsForm, &SchoolSettingsForm::notifySchoolLogoUpdate,
            qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::updateSchoolLogo);

}
