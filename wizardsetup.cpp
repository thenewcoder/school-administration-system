#include "wizardsetup.h"
#include "wizardintropage.h"
#include "wizarddatabasesetup.h"
#include "wizardusersetuppage.h"
#include "wizardsummarypage.h"
#include "settings.h"
#include "databasemanager.h"

#include <QVariant>
#include <QDir>
#include <QTranslator>
#include <QApplication>

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
        DatabaseManager::instance().addUser(username, password, fullname);
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
    QString location = field("location").toString();
    if (field("defaultLocation").toBool())
        return DATABASE_FILENAME;
    else
    {
        if (field("location").toString().isEmpty())
            return "";

        return QDir::toNativeSeparators(location);
    }
}

bool WizardSetup::getIsDefaultDatabase() const
{
    return field("defaultLocation").toBool();
}
