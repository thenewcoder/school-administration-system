#include "pageclassesform.h"
#include "ui_pageclassesform.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

#include "databasemanager.h"
#include "editclassdialog.h"
#include "class.h"

PageClassesForm::PageClassesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageClassesForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    // prepare the model
    mModel->setTable("class_summary");
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
        EditClassDialog add("Add New Class", this);

        if (add.exec() == QDialog::Accepted)
        {
            qDebug() << "clicked ok";

            // insert the new class into the database
            DatabaseManager::instance().addClass(add.getClass());
        }

    });

    connect(ui->btnEditClass, &QPushButton::clicked, [this] () {
        // get index and id for the selected row
        QModelIndex index = ui->tvClasses->currentIndex();

        if (index.isValid())
        {
            QString id = mModel->data(mModel->index(index.row(), 0)).toString();

            EditClassDialog edit("Edit Class", this);
            edit.setClass(DatabaseManager::instance().getClass(id));

            if (edit.exec() == QDialog::Accepted)
            {
                qDebug() << "Clicked ok";

                // update the database with the new class information

            }
        }
    });
}
