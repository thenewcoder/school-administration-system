#include "adminmenuform.h"
#include "ui_adminmenuform.h"

AdminMenuForm::AdminMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenuForm)
{
    ui->setupUi(this);

    // make the home button selected by default
    ui->menuListWidget->setCurrentRow(MenuItems::HOME);
}

AdminMenuForm::~AdminMenuForm()
{
    delete ui;
}
