#ifndef WIZARDSETUP_H
#define WIZARDSETUP_H

#include <QWidget>
#include <QWizard>

class WizardSetup : public QWizard
{
    Q_OBJECT

public:
    WizardSetup(QWidget *parent = Q_NULLPTR);

    // QDialog interface
public slots:
    void accept() override;
};

#endif // WIZARDSETUP_H
