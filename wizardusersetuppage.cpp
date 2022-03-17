#include "wizardusersetuppage.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QRegExpValidator>
#include <QApplication>

WizardUserSetupPage::WizardUserSetupPage(QWidget *parent)
    : QWizardPage(parent)
{
    // setup title and subtitle for the page
    setTitle(tr("Setup User Profile"));
    setSubTitle(tr("Create your user profile"));

    // setup the group box and the two radio buttons
    gbGroupBox = new QGroupBox;
    btnNewUser = new QRadioButton("Create New User");
    btnNewUser->setChecked(true);
    btnExistingUser = new QRadioButton("Use Existing Account");

    // prepare groupbox layout and add radio buttons
    QHBoxLayout *groupboxlayout = new QHBoxLayout;
    groupboxlayout->addWidget(btnNewUser);
    groupboxlayout->addWidget(btnExistingUser);
    groupboxlayout->setSpacing(30);
    gbGroupBox->setLayout(groupboxlayout);

    // create a validator for the username - 3 to 16 characters long
    QValidator *userValidator = new QRegExpValidator(QRegExp(".{3,16}"), this);

    // setup the username section
    lblName = new QLabel(tr("&Username:"));
    leUsername = new QLineEdit;
    leUsername->setPlaceholderText(tr("3-16 characters"));
    leUsername->setValidator(userValidator);
    lblName->setBuddy(leUsername);

    // create a password validator - 6 to 16 characters long
    QValidator *passValidator = new QRegExpValidator(QRegExp(".{6,16}"), this);

    // setup the password section
    lblPassword = new QLabel(tr("&Password:"));
    lePassword = new QLineEdit;
    lePassword->setEchoMode(QLineEdit::Password);
    lePassword->setPlaceholderText(tr("6-16 characters"));
    lePassword->setValidator(passValidator);
    lblPassword->setBuddy(lePassword);

    // setup the confirm password section
    lblConfirmPassword = new QLabel(tr("&Confirm Password:"));
    leConfirmPassword = new QLineEdit;
    leConfirmPassword->setEchoMode(QLineEdit::Password);
    leConfirmPassword->setPlaceholderText(tr("Re-type password"));
    leConfirmPassword->setValidator(passValidator);
    lblConfirmPassword->setBuddy(leConfirmPassword);

    // setup the full name section
    lblFullName = new QLabel(tr("&Full Name:"));
    leFullName = new QLineEdit;
    lblFullName->setBuddy(leFullName);

    // prepare the page layout and add widgets
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(gbGroupBox, 0, 0, 1, 4);
    layout->addWidget(lblName, 1, 0);
    layout->addWidget(leUsername, 1, 1, 1, 4);
    layout->addWidget(lblPassword, 2, 0);
    layout->addWidget(lePassword, 2, 1, 1, 4);
    layout->addWidget(lblConfirmPassword, 3, 0);
    layout->addWidget(leConfirmPassword, 3, 1, 1, 4);
    layout->addWidget(lblFullName, 4, 0);
    layout->addWidget(leFullName, 4, 1, 1, 4);

    setLayout(layout);

    // register fields
    registerField("newuser", btnNewUser);
    registerField("username*", leUsername);
    registerField("password*", lePassword);
    registerField("confirmPassword*", leConfirmPassword);
    registerField("fullname", leFullName);

    setupConnections();
}


bool WizardUserSetupPage::isComplete() const
{
    return (lePassword->hasAcceptableInput() &&
            leConfirmPassword->hasAcceptableInput() &&
            leUsername->hasAcceptableInput() &&
            lePassword->text() == leConfirmPassword->text()) ||
            btnExistingUser->isChecked();
}

void WizardUserSetupPage::setupConnections()
{
    connect(btnExistingUser, &QRadioButton::toggled, this, [this] (bool checked) {
        emit completeChanged();

        if (checked)
        {
            leUsername->setEnabled(false);
            lePassword->setEnabled(false);
            leConfirmPassword->setEnabled(false);
            leFullName->setEnabled(false);
        }
        else
        {
            leUsername->setEnabled(true);
            lePassword->setEnabled(true);
            leConfirmPassword->setEnabled(true);
            leFullName->setEnabled(true);
        }
    });
}


void WizardUserSetupPage::initializePage()
{
    // if the user chose create a new database, disable use existing account
    if (field("newdatabase").toBool())
    {
        btnExistingUser->setEnabled(false);
    }
    else
        btnExistingUser->setEnabled(true);
}


void WizardUserSetupPage::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        setTitle(qApp->translate("WizardUserSetupPage", "Setup User Profile"));
        setSubTitle(qApp->translate("WizardUserSetupPage", "Create your user profile"));
        btnNewUser->setText(qApp->translate("WizardUserSetupPage", "Create New User"));
        btnExistingUser->setText(qApp->translate("WizardUserSetupPage", "Use Existing Account"));
        lblName->setText(qApp->translate("WizardUserSetupPage", "&Username:"));
        leUsername->setPlaceholderText(qApp->translate("WizardUserSetupPage", "3-16 characters"));
        lblPassword->setText(qApp->translate("WizardUserSetupPage", "&Password:"));
        lePassword->setPlaceholderText(qApp->translate("WizardUserSetupPage", "6-16 characters"));
        lblConfirmPassword->setText(qApp->translate("WizardUserSetupPage", "&Confirm Password:"));
        leConfirmPassword->setPlaceholderText(qApp->translate("WizardUserSetupPage", "Re-type password"));
        lblFullName->setText(qApp->translate("WizardUserSetupPage", "&Full Name:"));
    }
}
