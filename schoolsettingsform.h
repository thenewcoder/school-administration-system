#ifndef SCHOOLSETTINGSFORM_H
#define SCHOOLSETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SchoolSettingsForm;
}

class SchoolSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SchoolSettingsForm(QWidget *parent = 0);
    ~SchoolSettingsForm();

    void loadDatabaseSettings();

signals:
    void notifySchoolLogoUpdate(const QPixmap &logo);
    void notifySchoolNameChanged(const QString &name);

private:
    void setupConnections();

private:
    Ui::SchoolSettingsForm *ui;
};

#endif // SCHOOLSETTINGSFORM_H
