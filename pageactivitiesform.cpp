#include "pageactivitiesform.h"
#include "ui_pageactivitiesform.h"

PageActivitiesForm::PageActivitiesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageActivitiesForm)
{
    ui->setupUi(this);
}

PageActivitiesForm::~PageActivitiesForm()
{
    delete ui;
}
