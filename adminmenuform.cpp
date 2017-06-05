#include "adminmenuform.h"
#include "ui_adminmenuform.h"

AdminMenuForm::AdminMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenuForm)
{
    ui->setupUi(this);
}

AdminMenuForm::~AdminMenuForm()
{
    delete ui;
}
