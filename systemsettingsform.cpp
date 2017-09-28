#include "systemsettingsform.h"
#include "ui_systemsettingsform.h"

#include "settings.h"

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

    ui->cbLanguages->setCurrentIndex(index);
}

void SystemSettingsForm::setupConnections()
{
    connect(ui->cbLanguages, SIGNAL(currentIndexChanged(int)), this, SLOT(onLanguageChanged(int)));
}

void SystemSettingsForm::onLanguageChanged(int index)
{
    if (index == 1) // chinese
        Settings::instance().setLanguage("zh_CN");
}
