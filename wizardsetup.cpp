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
#include <QTranslator>
#include <QApplication>
#include <QDebug>

WizardSetup::WizardSetup(QTranslator *translator, QWidget *parent)
    : QWizard(parent)
    , mTranslator(translator)
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

        // encrypt password before sending it off
        QString encryptedPassword = Login::instance().encryptString(password);
        DatabaseManager::instance().addUser(username, encryptedPassword, fullname);
    }

    QWizard::accept();
}

QString WizardSetup::getLanguage() const
{
    int index = field("language").toInt();
    if (index == 0)
        return "en_US";
    else if (index == 1)
        return "zh_CN";
    else if (index == 2)
        return "ko_KR";

    return "en_US"; // default value
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
