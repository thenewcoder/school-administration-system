#include "pagehomeform.h"
#include "ui_pagehomeform.h"

PageHomeForm::PageHomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHomeForm)
{
    ui->setupUi(this);
}

PageHomeForm::~PageHomeForm()
{
    delete ui;
}
