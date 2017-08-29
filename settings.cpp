#include "settings.h"

#include <QSettings>
#include <QDir>
#include <QFileInfo>

static const QString FILENAME = QDir::currentPath() + "/settings.ini";

Settings &Settings::instance()
{
    static Settings singleton;
    return singleton;
}

QString Settings::language() const
{
    return mSettings["lang"];
}

void Settings::setLanguage(const QString &lang)
{
    saveSetting("lang", lang);
}

QString Settings::databaseLocation() const
{
    return mSettings["location"];
}

void Settings::setDatabaseLocation(const QString &location)
{
    saveSetting("location", location);
}

QString Settings::databaseDriver() const
{
    return mSettings["driver"];
}

void Settings::setDatabaseDriver(const QString &driver)
{
    saveSetting("driver", driver);
}

void Settings::saveSetting(const QString &key, const QString &value)
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    settings.setValue(key, value);
    mSettings[key] = value;
}

Settings::Settings()
{
    if (settingsExists())
    {
        // read settings from the settings.ini file
        loadSettings();
    }
}

bool Settings::settingsExists() const
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    return settings.value("setup", false).toBool();
}

void Settings::setSettingsExists()
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    settings.setValue("setup", true);
}

bool Settings::isDefaultDatabase() const
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    return settings.value("defaultDatabase", true).toBool();
}

void Settings::setIsDefaultDatabase(bool isDefault)
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    settings.setValue("defaultDatabase", isDefault);
}

void Settings::loadSettings()
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    for (auto &s : settings.allKeys())
    {
        mSettings.insert(s, settings.value(s).toString());
    }
}

void Settings::saveSettings(QHash<QString, QString> &values)
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    for (auto &k : values.keys())
    {
        settings.setValue(k, values[k]);
        mSettings[k] = values[k];
    }
}
