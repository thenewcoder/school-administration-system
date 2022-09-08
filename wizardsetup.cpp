#include "wizardsetup.h"
#include "wizardintropage.h"
#include "wizarddatabasesetup.h"
#include "wizardusersetuppage.h"
#include "wizardsummarypage.h"
#include "settings.h"
#include "databasemanager.h"
#include "login.h"

#include <QVariant>
#include <QDir>
#include <QApplication>


WizardSetup::WizardSetup(QWidget *parent)
    : QWizard(parent)
{
    // make the font size a little bigger than default
    QFont f(font());
    f.setPointSize(10);
    setFont(f);

    // add wizard pages
    addPage(new WizardIntroPage(this));
    addPage(new WizardDatabaseSetup(this));
    addPage(new WizardUserSetupPage(this));
    addPage(new WizardSummaryPage(this));

    setWindowTitle(tr("New Installation Setup"));

    // set the wizard window size
    resize(460, 420);
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
        int userType = 1; // NOTE: change this later to get data from combobox

        // encrypt password before sending it off  NOTE: add usertype id to add user as well
        QString encryptedPassword = Login::instance().encryptString(password);
        if (DatabaseManager::instance().addUser(username, encryptedPassword, fullname, userType))
        {
            // if new user successfully added - update preferred language
            int languagePref = field("language").toInt();
            DatabaseManager::instance().updateUserLanguagePreferenceByUsername(languagePref, username);
        }
    }

    QWizard::accept();
}

QString WizardSetup::getLanguage() const
{
    int index = field("language").toInt();

    switch(index)
    {
    case Settings::ENGLISH:
        return "en_US";
    case Settings::CHINESE:
        return "zh_CN";
    case Settings::KOREAN:
        return "ko_KR";
    default:
        return "en_US";
    }
}

QString WizardSetup::getDatabaseDriver() const
{
    QString driver = field("databasedriver").toString();
    if (driver == "SQLite")
        return "QSQLITE";

    return "QSQLITE"; // for now...
}

QString WizardSetup::getLocation() const
{
    if (field("defaultLocation").toBool())
        return DATABASE_FILENAME;
    else  // user specify a location
    {
        QString location = field("location").toString();

        if (location.isEmpty())
            return DATABASE_FILENAME;
        else if (field("newdatabase").toBool()) // user wants to create a new database
            return QDir::toNativeSeparators(QDir(location).filePath(DATABASE_FILENAME));
        else  // user wants to use an existing database
            return QDir::toNativeSeparators(location);
    }
}

bool WizardSetup::getIsDefaultDatabase() const
{
    return field("defaultLocation").toBool();
}
