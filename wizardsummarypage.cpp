﻿#include "wizardsummarypage.h"

#include <QLabel>
#include <QGridLayout>
#include <QVariant>
#include <QApplication>

WizardSummaryPage::WizardSummaryPage(QWidget *parent)
    : QWizardPage(parent)
{
    // set title of the page
    setTitle(tr("Summary"));

    // setup the username label
    lblUsername = new QLabel(tr("Username:"));
    lblUsernameResult = new QLabel("");

    // setup the database type label
    lblDatabaseType = new QLabel(tr("Database Type:"));
    lblDatabaseTypeResult = new QLabel("");

    // setup the database location label - initialize it to 'Local' for now
    lblDatabaseLocation = new QLabel(tr("Database Location:"));
    lblDatabaseLocationResult = new QLabel(tr("Local")); // for now... remember to change translation event if change this

    // setup the full name label
    lblFullName = new QLabel(tr("Full name:"));
    lblFullNameResult = new QLabel("");

    // prepare the page layout and add widgets
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(lblUsername, 0, 0, 1, 1);
    layout->addWidget(lblUsernameResult, 0, 1, 1, 2);
    layout->addWidget(lblDatabaseType, 1, 0, 1, 1);
    layout->addWidget(lblDatabaseTypeResult, 1, 1, 1, 2);
    layout->addWidget(lblDatabaseLocation, 2, 0);
    layout->addWidget(lblDatabaseLocationResult, 2, 1, 1, 2);
    layout->addWidget(lblFullName, 3, 0);
    layout->addWidget(lblFullNameResult, 3, 1, 1, 2);

    setLayout(layout);
}


void WizardSummaryPage::initializePage()
{
    lblUsernameResult->setText(field("username").toString());
    lblDatabaseTypeResult->setText(field("databasedriver").toString());
    lblFullNameResult->setText(field("fullname").toString());
}


void WizardSummaryPage::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        setTitle(qApp->translate("WizardSummaryPage", "Summary"));
        lblUsername->setText(qApp->translate("WizardSummaryPage", "Username:"));
        lblDatabaseType->setText(qApp->translate("WizardSummaryPage", "Database Type:"));
        lblDatabaseLocation->setText(qApp->translate("WizardSummaryPage", "Database Location:"));
        lblDatabaseLocationResult->setText(qApp->translate("WizardSummaryPage", "Local"));
        lblFullName->setText(qApp->translate("WizardSummaryPage", "Full name:"));
    }
}
