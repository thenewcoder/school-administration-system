#ifndef WIZARDSETUP_H
#define WIZARDSETUP_H

#include <QWidget>
#include <QWizard>

class WizardSetup : public QWizard
{
    Q_OBJECT

public:
    WizardSetup(QWidget *parent = nullptr);

    // QDialog interface
public slots:
    void accept() override;

private:
    QString getLanguage() const;
    QString getDatabaseDriver() const;
    QString getLocation() const;
    bool getIsDefaultDatabase() const;
};

#endif // WIZARDSETUP_H
