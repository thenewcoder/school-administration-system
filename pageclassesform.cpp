#include "pageclassesform.h"
#include "ui_pageclassesform.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

PageClassesForm::PageClassesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageClassesForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    // prepare the model
    mModel->setTable("class");
    mModel->select();


    // set up the view
    ui->tvClasses->setModel(mModel);
    ui->tvClasses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvClasses->setSelectionMode(QAbstractItemView::SingleSelection);

    setupConnections();
}

PageClassesForm::~PageClassesForm()
{
    delete ui;
}

void PageClassesForm::setupConnections()
{
    connect(ui->btnAddClass, &QPushButton::clicked, [this] () {

    });
}
