#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHash>

class QTranslator;

class Settings
{
public:
    enum LANGUAGE
    {
        ENGLISH,
        CHINESE,
        KOREAN
    };

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

    bool isDefaultDatabase() const;
    void setIsDefaultDatabase(bool isDefault);

    void saveSetting(const QString &key, const QString &value);

    QTranslator* getTranslator() const;

private:
    explicit Settings();
    ~Settings();
    Settings(const Settings& rhs) = delete;
    Settings& operator=(const Settings& rhs) = delete;

    void loadSettings();
    void saveSettings(QHash<QString, QString> &values);

private:
    QHash<QString, QString> mSettings;

    QTranslator *mTranslator;

    bool mSettingsExists;
};

#endif // SETTINGS_H
