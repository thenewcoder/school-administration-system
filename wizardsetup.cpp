#include "wizardsetup.h"
#include "wizardintropage.h"
#include "wizardusersetuppage.h"
#include "wizarddatabasesetup.h"
#include "wizardsummarypage.h"
#include <QDebug>

WizardSetup::WizardSetup(QWidget *parent)
    : QWizard(parent)
{
    // make the font size a little bigger than default
    QFont f(font());
    f.setPointSize(10);
    setFont(f);

    // add wizard pages
    addPage(new WizardIntroPage);
    addPage(new WizardDatabaseSetup);
    addPage(new WizardUserSetupPage);
    addPage(new WizardSummaryPage);

    setWindowTitle(tr("New Installation Setup"));

    // make the wizard window a fixed size
    setFixedSize(460, 420);
}

void WizardSetup::accept()
{
    qDebug() << field("username").toString();
    qDebug() << field("password").toString();
    qDebug() << field("location").toString();
    qDebug() << field("language").toString();

    QWizard::accept();
}
