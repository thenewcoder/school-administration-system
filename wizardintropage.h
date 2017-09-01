#ifndef WIZARDINTROPAGE_H
#define WIZARDINTROPAGE_H

#include <QWidget>
#include <QWizardPage>

class QLabel;
class QComboBox;
class QTranslator;

class WizardIntroPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit WizardIntroPage(QWidget *parent = nullptr);

private slots:
    void changeLanguage(int index);

private:
    void resetComboBox();

private:
    QLabel *lblIntroText;
    QLabel *lblLanguage;

    QComboBox *cbLanguage;

    QTranslator *translator;

    int mLangIndex;

    // QWidget interface
protected:
    virtual void changeEvent(QEvent *e) override;
};

#endif // WIZARDINTROPAGE_H
