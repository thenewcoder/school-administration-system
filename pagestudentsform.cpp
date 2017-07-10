#include "pagestudentsform.h"
#include "ui_pagestudentsform.h"

PageStudentsForm::PageStudentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageStudentsForm)
{
    ui->setupUi(this);
}

PageStudentsForm::~PageStudentsForm()
{
    delete ui;
}
