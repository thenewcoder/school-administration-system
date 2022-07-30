#ifndef SCHOOLSETTINGSFORM_H
#define SCHOOLSETTINGSFORM_H

#include <QWidget>
#include "school.h"

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
    void loadDatabaseSettingsRestricted();

signals:
    void notifySchoolLogoUpdate(const QPixmap &logo);
    void notifySchoolNameChanged(const QString &name);

private:
    void setupConnections();
    void toggleSaveButton(bool state);

public slots:
    void onTeachersOrUsersChanged();

private slots:
    void onSettingsHaveChanged();

private:
    Ui::SchoolSettingsForm *ui;

    School mSchool;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // SCHOOLSETTINGSFORM_H
