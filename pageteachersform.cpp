#include "pageteachersform.h"
#include "ui_pageteachersform.h"

PageTeachersForm::PageTeachersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTeachersForm)
{
    ui->setupUi(this);
}

PageTeachersForm::~PageTeachersForm()
{
    delete ui;
}
