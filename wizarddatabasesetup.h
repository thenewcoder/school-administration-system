﻿#ifndef WIZARDDATABASESETUP_H
#define WIZARDDATABASESETUP_H

#include <QWidget>
#include <QWizardPage>

class QLabel;
class QComboBox;
class QCheckBox;
class QGroupBox;
class QRadioButton;
class QLineEdit;
class QPushButton;

class WizardDatabaseSetup : public QWizardPage
{
    Q_OBJECT
public:
    explicit WizardDatabaseSetup(QWidget *parent = nullptr);

    // QWizardPage interface
    bool isComplete() const override;

private:
    void setupConnections();
    bool databaseExists() const;

private:
    QLabel *lblDatabaseType;
    QLabel *lblLocation;

    QComboBox *cbDatabaseDrivers;
    QCheckBox *chbDefaultLocation;
    QGroupBox *gbGroupBox;

    QRadioButton *btnNewDatabase;
    QRadioButton *btnExistingDatabase;

    QLineEdit *leLocation;

    QPushButton *btnChangeLocation;

    QLabel *lblDatabaseMessage;


    // QWidget interface
protected:
    virtual void changeEvent(QEvent *e) override;
};

#endif // WIZARDDATABASESETUP_H
