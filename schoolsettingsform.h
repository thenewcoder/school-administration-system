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

signals:
    void notifySchoolLogoUpdate(const QPixmap &logo);

private:
    void setupConnections();

    void loadDatabaseSettings();

private:
    Ui::SchoolSettingsForm *ui;
};

#endif // SCHOOLSETTINGSFORM_H
