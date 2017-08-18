#ifndef WIZARDSUMMARYPAGE_H
#define WIZARDSUMMARYPAGE_H

#include <QWidget>
#include <QWizardPage>

class QLabel;

class WizardSummaryPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit WizardSummaryPage(QWidget *parent = nullptr);

    // QWizardPage interface
    void initializePage() override;

private:
    QLabel *lblUsername;
    QLabel *lblDatabaseType;
    QLabel *lblDatabaseLocation;
    QLabel *lblFullName;

    QLabel *lblUsernameResult;
    QLabel *lblDatabaseTypeResult;
    QLabel *lblDatabaseLocationResult;
    QLabel *lblFullNameResult;
};

#endif // WIZARDSUMMARYPAGE_H
