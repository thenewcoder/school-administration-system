#include "systemsettingsform.h"
#include "ui_systemsettingsform.h"

#include <QTranslator>
#include <QMessageBox>
#include "settings.h"
#include "databasemanager.h"
#include "login.h"


SystemSettingsForm::SystemSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingsForm)
{
    ui->setupUi(this);

    // set the language box
    setLanguage(Settings::instance().language());

    setupConnections();
}

SystemSettingsForm::~SystemSettingsForm()
{
    delete ui;
}

void SystemSettingsForm::setLanguage(const QString &locale)
{
    int index = 0; // default - English language

    if (locale == "zh_CN")
        index = 1;

    int userLangPref = Login::instance().getUserData().languagePreference();

    if (userLangPref != index)
    {
        index = userLangPref;
        onLanguageChanged(userLangPref);
    }

    ui->cbLanguages->setCurrentIndex(index);
}

void SystemSettingsForm::setupConnections()
{
    connect(ui->cbLanguages, SIGNAL(currentIndexChanged(int)), this, SLOT(onLanguageChanged(int)));
}

void SystemSettingsForm::onLanguageChanged(int index)
{
    if (index == Settings::ENGLISH)
    {
        Settings::instance().setLanguage("en_US");
        Settings::instance().getTranslator()->load("translations/trans_en_US");
    }
    else if (index == Settings::CHINESE)
    {
        Settings::instance().setLanguage("zh_CN");
        Settings::instance().getTranslator()->load("translations/trans_zh_CN");
    }

    // don't do anything if nothing was changed
    if (Login::instance().getUserData().languagePreference() != index)
    {
        // update user language preference
        DatabaseManager::instance().updateUserLanguagePreference(index, Login::instance().getUserData().userId());
    }
}

void SystemSettingsForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QWidget::changeEvent(e);
}
