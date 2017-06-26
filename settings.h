#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHash>

class Settings
{
public:
    static Settings& instance();

    QString language() const;
    void setLanguage(const QString &lang);

private:
    explicit Settings();
    Settings(const Settings& rhs) = delete;
    Settings& operator=(const Settings& rhs) = delete;

    void loadSettings();
    void saveSettings(QHash<QString, QString> &values);

private:
    QHash<QString, QString> mSettings;
};

#endif // SETTINGS_H
