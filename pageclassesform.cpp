#include "pageclassesform.h"
#include "ui_pageclassesform.h"

PageClassesForm::PageClassesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageClassesForm)
{
    ui->setupUi(this);
}

PageClassesForm::~PageClassesForm()
{
    delete ui;
}
