#include "personalprofileform.h"
#include "ui_personalprofileform.h"

#include "login.h"
#include "user.h"

PersonalProfileForm::PersonalProfileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalProfileForm)
{
    ui->setupUi(this);

    // make the Save buttons disabled by default
    ui->btnSave->setEnabled(false);
    ui->btnResetPersonal->setEnabled(false);
    ui->btnChangePassword->setEnabled(false);

    setupConnections();
}

PersonalProfileForm::~PersonalProfileForm()
{
    delete ui;
}

void PersonalProfileForm::setupUser()
{
    QString username = Login::instance().username();
    QString fullname = Login::instance().fullname();

    // add the values to the line edits
    ui->leUsername->setText(username);
    ui->leFullName->setText(fullname);

    // add the values the user variable
    mUser.setUsername(username);
    mUser.setFullName(fullname);
}

void PersonalProfileForm::onProfileHasChanged()
{
    // start out with no changes has been made
    bool hasChanged = false;

    // check every field to see if any changes have been made
    if (mUser.username() != ui->leUsername->text())
    {
        // check if username is already taken
        if(!Login::instance().isUsernameTaken(ui->leUsername->text()))
            hasChanged = true;
    }
    else if (mUser.fullName() != ui->leFullName->text())
        hasChanged = true;

    // change the state of the buttons to reflect the change
    toggleSaveButton(hasChanged);
}

void PersonalProfileForm::onPasswordHasChanged()
{
    // check so that the password fields aren't empty and that they are the same
    if (!ui->leNewPassword->text().isEmpty() &&  // not empty
            ui->leNewPassword->text() == ui->leConfirmNewPassword->text() && // not equal
            Login::instance().isValidPassword(ui->leNewPassword->text()))  // is a valid password
    {
        ui->btnChangePassword->setEnabled(true);
    }
    else
        ui->btnChangePassword->setEnabled(false);
}

void PersonalProfileForm::setupConnections()
{
    // create connections to check for line edit changes
    connect(ui->leUsername, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->leFullName, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->leNewPassword, SIGNAL(textEdited(QString)), this, SLOT(onPasswordHasChanged()));
    connect(ui->leConfirmNewPassword, SIGNAL(textEdited(QString)), this, SLOT(onPasswordHasChanged()));

    connect(ui->btnSave, &QPushButton::clicked, [this] () {
        User user = Login::instance().getUserData();
        user.setUsername(ui->leUsername->text());
        user.setFullName(ui->leFullName->text());
        Login::instance().updateUserData(user);
        mUser = user; // change the new default values
        toggleSaveButton(false);

        // send a signal so that the fullname at the admin menu form will update
        emit notifyFullnameChanged(user.fullName());
    });

    connect(ui->btnChangePassword, &QPushButton::clicked, [this] () {

        // update with the new password  TODO: make the password update separate from the profile data
        User user = Login::instance().getUserData();
        user.setPassword(ui->leNewPassword->text());

        if (Login::instance().updateUserData(user))
        {
            // clear the line edits again
            ui->leNewPassword->setText("");
            ui->leConfirmNewPassword->setText("");
        }
    });

    // reset the user profile data
    connect(ui->btnResetPersonal, &QPushButton::clicked, [this] () {
        ui->leUsername->setText(mUser.username());
        ui->leFullName->setText(mUser.fullName());
        toggleSaveButton(false);
    });
}

void PersonalProfileForm::toggleSaveButton(bool state)
{
    ui->btnSave->setEnabled(state);
    ui->btnResetPersonal->setEnabled(state);
}

void PersonalProfileForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QWidget::changeEvent(e);
}
