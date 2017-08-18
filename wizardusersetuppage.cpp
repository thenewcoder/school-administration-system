#include "wizardusersetuppage.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QRegExpValidator>

WizardUserSetupPage::WizardUserSetupPage(QWidget *parent)
    : QWizardPage(parent)
{
    // setup title and subtitle for the page
    setTitle(tr("Setup User Profile"));
    setSubTitle(tr("Create your user profile"));

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

    // register fields
    registerField("username*", leUsername);
    registerField("password*", lePassword);
    registerField("confirmPassword*", leConfirmPassword);
    registerField("fullname", leFullName);

    // prepare the page layout and add widgets
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(lblName, 0, 0);
    layout->addWidget(leUsername, 0, 1);
    layout->addWidget(lblPassword, 1, 0);
    layout->addWidget(lePassword, 1, 1);
    layout->addWidget(lblConfirmPassword, 2, 0);
    layout->addWidget(leConfirmPassword, 2, 1);
    layout->addWidget(lblFullName, 3, 0);
    layout->addWidget(leFullName, 3, 1);

    setLayout(layout);
}


bool WizardUserSetupPage::isComplete() const
{
    return lePassword->hasAcceptableInput() &&
           leConfirmPassword->hasAcceptableInput() &&
           leUsername->hasAcceptableInput() &&
           lePassword->text() == leConfirmPassword->text();
}
