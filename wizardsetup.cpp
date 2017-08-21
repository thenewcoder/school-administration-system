#include "wizardsetup.h"
#include "wizardintropage.h"
#include "wizarddatabasesetup.h"
#include "wizardusersetuppage.h"
#include "wizardsummarypage.h"
#include "settings.h"
#include "databasemanager.h"

#include <QVariant>

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
    // save locally needed settings to the settings file
    Settings::instance().setIsDefaultDatabase(getIsDefaultDatabase());
    Settings::instance().setDatabaseLocation(getLocation());
    Settings::instance().setLanguage(getLanguage());
    Settings::instance().setDatabaseDriver(getDatabaseDriver());
    Settings::instance().setSettingsExists();

    // if user doesn't have a previous account add a new one
    if (field("newuser").toBool())
    {
        QString username = field("username").toString();
        QString password = field("password").toString();
        QString fullname = field("fullname").toString();
        DatabaseManager::instance().addUser(username, password, fullname);
    }

    QWizard::accept();
}

QString WizardSetup::getLanguage() const
{
    QString language = field("language").toString();
    if (language == "English")
        return "en_US";
    else if (language == "Chinese")
        return "zh_CN";
    else if (language == "Korean")
        return "ko_KR";

    return "en_US"; // default value
}

QString WizardSetup::getDatabaseDriver() const
{
    QString driver = field("databasedriver").toString();
    if (driver == "SQLite")
        return "QSQLITE";

    return "SQLite"; // for now...
}

QString WizardSetup::getLocation() const
{
    QString location = field("location").toString();
    if (field("defaultLocation").toBool())
        return "";
    else
    {
        if (field("location").toString().isEmpty())
            return "";

        return location;
    }
}

bool WizardSetup::getIsDefaultDatabase() const
{
    return field("defaultLocation").toBool();
}
