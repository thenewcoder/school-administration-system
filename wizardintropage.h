#ifndef WIZARDINTROPAGE_H
#define WIZARDINTROPAGE_H

#include <QWidget>
#include <QWizardPage>

class QLabel;
class QComboBox;

class WizardIntroPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit WizardIntroPage(QWidget *parent = nullptr);

private:
    QLabel *lblIntroText;
    QLabel *lblLanguage;

    QComboBox *cbLanguage;
};

#endif // WIZARDINTROPAGE_H
