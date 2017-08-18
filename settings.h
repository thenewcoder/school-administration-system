#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHash>

class Settings
{
public:
    static Settings& instance();

    QString language() const;
    void setLanguage(const QString &lang);

    QString databaseLocation() const;
    void setDatabaseLocation(const QString &location);

    QString databaseDriver() const;
    void setDatabaseDriver(const QString &driver);

    bool settingsExists() const;
    void setSettingsExists();

    void saveSetting(const QString &key, const QString &value);

private:
    explicit Settings();
    Settings(const Settings& rhs) = delete;
    Settings& operator=(const Settings& rhs) = delete;

    void loadSettings();
    void saveSettings(QHash<QString, QString> &values);

private:
    QHash<QString, QString> mSettings;

    bool mSettingsExists;
};

#endif // SETTINGS_H
