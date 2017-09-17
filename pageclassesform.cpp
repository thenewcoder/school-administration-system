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

    // set header names
    mModel->setHeaderData(FIELDS::GRADE, Qt::Horizontal, tr("Grade"));
    mModel->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModel->setHeaderData(FIELDS::SUBJECT, Qt::Horizontal, tr("Subject"));
    mModel->setHeaderData(FIELDS::ROOM, Qt::Horizontal, tr("Classroom"));
    mModel->setHeaderData(FIELDS::TEACHERS, Qt::Horizontal, tr("Teachers"));
    mModel->setHeaderData(FIELDS::ENROLLMENT, Qt::Horizontal, tr("Enrollment"));

    // set up the view
    ui->tvClasses->setModel(mModel);
    ui->tvClasses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvClasses->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvClasses->hideColumn(FIELDS::ID); // hide id column
    ui->tvClasses->resizeRowsToContents();

    setupConnections();
}

PageClassesForm::~PageClassesForm()
{
    delete ui;
}

void PageClassesForm::updateClassTable()
{
    mModel->select();
}

void PageClassesForm::setupConnections()
{
    // Add a new class
    connect(ui->btnAddClass, &QPushButton::clicked, [this] () {
        EditClassDialog add(tr("Add New Class"), this);

        if (add.exec() == QDialog::Accepted)
        {
            // insert the new class into the database
            DatabaseManager::instance().addClass(add.getClass());
            updateClassTable(); // update the table view

            // Let connected slots know class table has changed
            emit notifyClassesChanged();
        }

    });

    // Edit an existing class
    connect(ui->btnEditClass, &QPushButton::clicked, [this] () {
        // get index and id for the selected row
        QModelIndex index = ui->tvClasses->currentIndex();

        if (index.isValid())
        {
            QString id = mModel->data(mModel->index(index.row(), 0)).toString();

            EditClassDialog edit(tr("Edit Class"), this, true);
            edit.setClass(DatabaseManager::instance().getClass(id));

            if (edit.exec() == QDialog::Accepted)
            {
                // get the class info from the dialog and set the class Id
                Class c = edit.getClass();
                c.setClassId(id);

                // update the database with the new class information
                DatabaseManager::instance().saveClassData(c);
                updateClassTable(); // update the table view

                // Let connected slots know class table has changed
                emit notifyClassesChanged();
            }
        }
    });

    // Delete a class
    connect(ui->btnDeleteClass, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvClasses->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Class"),
                                              tr("Are you sure you want to delete the selected class?\n"
                                              "This action cannot be undone!"),
                                              QMessageBox::Ok, QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                // get the selected id and delete the class
                QString id = mModel->data(mModel->index(index.row(), 0)).toString();
                DatabaseManager::instance().removeClass(id);
                updateClassTable(); // update the table view

                // Let connected slots know class table has changed
                emit notifyClassesChanged();
            }
        }
    });

    // Refresh the table
    connect(ui->btnRefresh, &QPushButton::clicked, this, &PageClassesForm::updateClassTable);
}
