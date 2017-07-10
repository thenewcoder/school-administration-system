#include "pagesettingsform.h"
#include "ui_pagesettingsform.h"

PageSettingsForm::PageSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSettingsForm)
{
    ui->setupUi(this);
}

PageSettingsForm::~PageSettingsForm()
{
    delete ui;
}
