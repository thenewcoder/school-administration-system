#include "settings.h"

#include <QSettings>
#include <QDir>

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
    mSettings["lang"] = lang;
}

Settings::Settings()
{
    QSettings settings(FILENAME, QSettings::IniFormat);
    if (settings.allKeys().size() == 0)
    {
        // create a fresh settings.ini file with default values
        settings.setValue("lang", "en_US");
    }

    // read settings from the settings.ini file
    loadSettings();


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
