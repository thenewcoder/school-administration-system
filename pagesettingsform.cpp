#include "pagesettingsform.h"
#include "ui_pagesettingsform.h"

#include "schoolsettingsform.h"
#include "personalprofileform.h"
#include "systemsettingsform.h"
#include "adminmenuform.h"
#include "teachermenuform.h"
#include "personalprofileform.h"
#include "pagehomeform.h"
#include "usermanagerform.h"
#include "login.h"

PageSettingsForm::PageSettingsForm(PageHomeForm *pageHomeForm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSettingsForm),
    mPageHomeForm(pageHomeForm),
    mSchoolSettingsForm(new SchoolSettingsForm(this)),
    mPersonalProfileForm(new PersonalProfileForm(this)),
    mSystemSettingsForm(new SystemSettingsForm(this)),
    mUserManagerForm(nullptr)
{
    ui->setupUi(this);

    // currently logged in user type
    loggedInUserType = Login::instance().getUserType();

    // Add tabs to the settings tab widget
    ui->twSettingsPages->addTab(mSchoolSettingsForm, tr("School Settings"));
    ui->twSettingsPages->addTab(mPersonalProfileForm, tr("Personal Info"));
    ui->twSettingsPages->addTab(mSystemSettingsForm, tr("System Settings"));

    if (loggedInUserType == Login::UserType::Admin)
    {
        mUserManagerForm = new UserManagerForm(this);
        ui->twSettingsPages->addTab(mUserManagerForm, tr("Users"));
    }

    setupConnections();

    if (loggedInUserType == Login::UserType::Admin)
        mSchoolSettingsForm->loadDatabaseSettings();
    else
        mSchoolSettingsForm->loadDatabaseSettingsRestricted();
}

PageSettingsForm::~PageSettingsForm()
{
    delete ui;
}

void PageSettingsForm::setupConnections()
{  
    if (loggedInUserType == Login::UserType::Admin)
    {
        // update the school logo when the settings logo has been changed
        connect(mSchoolSettingsForm, &SchoolSettingsForm::notifySchoolLogoUpdate,
                qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::updateSchoolLogo);

        connect(qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::notifyUserLogon,
                mPersonalProfileForm, &PersonalProfileForm::setupUser);

        // connect signal from personal settings when user changes his/her username
        connect(mPersonalProfileForm, &PersonalProfileForm::notifyFullnameChanged,
                qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::onFullnameChanged);

        connect(qobject_cast<AdminMenuForm*>(this->parent()), &AdminMenuForm::notifyTeachersUpdated,
                mSchoolSettingsForm, &SchoolSettingsForm::onTeachersOrUsersChanged);
    }
    else if (loggedInUserType == Login::UserType::Teacher)
    {
        // update the school logo when the settings logo has been changed
        connect(mSchoolSettingsForm, &SchoolSettingsForm::notifySchoolLogoUpdate,
                qobject_cast<TeacherMenuForm*>(this->parent()), &TeacherMenuForm::updateSchoolLogo);

        connect(qobject_cast<TeacherMenuForm*>(this->parent()), &TeacherMenuForm::notifyUserLogon,
                mPersonalProfileForm, &PersonalProfileForm::setupUser);

        // connect signal from personal settings when user changes his/her username
        connect(mPersonalProfileForm, &PersonalProfileForm::notifyFullnameChanged,
                qobject_cast<TeacherMenuForm*>(this->parent()), &TeacherMenuForm::onFullnameChanged);

        connect(qobject_cast<TeacherMenuForm*>(this->parent()), &TeacherMenuForm::notifyTeachersUpdated,
                mSchoolSettingsForm, &SchoolSettingsForm::onTeachersOrUsersChanged);
    }

    connect(mUserManagerForm, &UserManagerForm::notifyUsersChanged, mSchoolSettingsForm, &SchoolSettingsForm::onTeachersOrUsersChanged);

    // to let the school name update...TODO: find a better way, too hackish
    connect(mSchoolSettingsForm, &SchoolSettingsForm::notifySchoolNameChanged, mPageHomeForm, &PageHomeForm::onSchoolNameChanged);
}

void PageSettingsForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        ui->twSettingsPages->setTabText(0, tr("School Settings"));
        ui->twSettingsPages->setTabText(1, tr("Personal Info"));
        ui->twSettingsPages->setTabText(2, tr("System Settings"));
        ui->twSettingsPages->setTabText(3, tr("Users"));
    }
    QWidget::changeEvent(e);
}

