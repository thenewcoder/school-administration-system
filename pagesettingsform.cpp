#include "pagesettingsform.h"
#include "ui_pagesettingsform.h"

#include "schoolsettingsform.h"
#include "personalprofileform.h"
#include "adminmenuform.h"
#include "personalprofileform.h"
#include "pagehomeform.h"

PageSettingsForm::PageSettingsForm(PageHomeForm *pageHomeForm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSettingsForm),
    mPageHomeForm(pageHomeForm),
    mSchoolSettingsForm(new SchoolSettingsForm(this)),
    mPersonalProfileForm(new PersonalProfileForm(this))
{
    ui->setupUi(this);

    // Add tabs to the settings tab widget
    ui->twSettingsPages->addTab(mSchoolSettingsForm, tr("School Settings"));
    ui->twSettingsPages->addTab(mPersonalProfileForm, tr("Personal Info"));

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

    connect(qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::notifyUserLogon,
            mPersonalProfileForm, &PersonalProfileForm::setupUser);

    // to let the school name update...TODO: find a better way, too hackish
    connect(mSchoolSettingsForm, &SchoolSettingsForm::notifySchoolNameChanged, mPageHomeForm, &PageHomeForm::onSchoolNameChanged);

    // connect signal from personal settings when user changes his/her username
    connect(mPersonalProfileForm, &PersonalProfileForm::notifyFullnameChanged,
            qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::onFullnameChanged);
}

