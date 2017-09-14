#include "personalprofileform.h"
#include "ui_personalprofileform.h"

#include "login.h"
#include "user.h"

PersonalProfileForm::PersonalProfileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalProfileForm),
    mSettingsChanged(false)
{
    ui->setupUi(this);

    // make the Save buttons disabled by default
    ui->btnSave->setEnabled(false);
    ui->btnResetPersonal->setEnabled(false);
    //ui->btnChangePassword->setEnabled(false);

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

void PersonalProfileForm::onUsernameChanged(const QString &change)
{
    // TODO: refactor this and the next method
    if (change != mUser.username())
    {   
        // check if username is already in use
        if (Login::instance().isUsernameTaken(change))
        {
            // TODO: add a proper way of telling the user - eg. colors
            // for now just erase the change
            ui->leUsername->setText(mUser.username());
        }

        mPendingChanges["username"] = change;
        mSettingsChanged = true;
        toggleSaveButton(true);
    }
    else
    {
        if (mPendingChanges.contains("username"))
            mPendingChanges.remove("username");
        if (mPendingChanges.size() == 0 && mSettingsChanged)
        {
            mSettingsChanged = false;
            toggleSaveButton(false);
        }
    }
}

void PersonalProfileForm::onFullnameChanged(const QString &change)
{
    if (change != mUser.fullName())
    {
        mPendingChanges["fullname"] = change;
        mSettingsChanged = true;
        toggleSaveButton(true);
    }
    else
    {
        if (mPendingChanges.contains("fullname"))
            mPendingChanges.remove("fullname");
        if (mPendingChanges.size() == 0 && mSettingsChanged)
        {
            mSettingsChanged = false;
            toggleSaveButton(false);
        }
    }
}

void PersonalProfileForm::setupConnections()
{
    // create connections to check for line edit changes
    connect(ui->leUsername, SIGNAL(textEdited(QString)), this, SLOT(onUsernameChanged(QString)));
    connect(ui->leFullName, SIGNAL(textEdited(QString)), this, SLOT(onFullnameChanged(QString)));

    connect(ui->btnSave, &QPushButton::clicked, [this] () {
        User user = Login::instance().getUserData();
        user.setUsername(ui->leUsername->text());
        user.setFullName(ui->leFullName->text());
        Login::instance().updateUserData(user);
        mUser = user; // change the new default values
        mPendingChanges.clear(); // empty the pending changes
        toggleSaveButton(false);

        // send a signal so the fullname at the admin menu form will update
        emit notifyFullnameChanged(user.fullName());
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

    // reset the user profile data
    connect(ui->btnResetPersonal, &QPushButton::clicked, [this] () {
        ui->leUsername->setText(mUser.username());
        ui->leFullName->setText(mUser.fullName());
        mPendingChanges.clear();
        toggleSaveButton(false);
    });
}

void PersonalProfileForm::toggleSaveButton(bool state)
{
    ui->btnSave->setEnabled(state);
    ui->btnResetPersonal->setEnabled(state);
}
