#ifndef WIZARDUSERSETUPPAGE_H
#define WIZARDUSERSETUPPAGE_H

#include <QWidget>
#include <QWizardPage>

class QLabel;
class QLineEdit;
class QGroupBox;
class QRadioButton;

class WizardUserSetupPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit WizardUserSetupPage(QWidget *parent = nullptr);

    // QWizardPage interface
    bool isComplete() const override;
    void initializePage() override;

private:
    void setupConnections();

private:
    QGroupBox *gbGroupBox;
    QRadioButton *btnNewUser;
    QRadioButton *btnExistingUser;

    QLabel *lblName;
    QLabel *lblPassword;
    QLabel *lblConfirmPassword;
    QLabel *lblFullName;

    QLineEdit *leUsername;
    QLineEdit *lePassword;
    QLineEdit *leConfirmPassword;
    QLineEdit *leFullName;

};

#endif // WIZARDUSERSETUPPAGE_H
