#include "pageteachersform.h"
#include "ui_pageteachersform.h"

#include "databasemanager.h"
#include "editteacherdialog.h"
#include "teacher.h"

#include <QSqlRelationalTableModel>
#include <QDebug>


PageTeachersForm::PageTeachersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTeachersForm),
    mModel(new QSqlRelationalTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("teacher");
    mModel->setRelation(2, QSqlRelation("gender", "genderId", "type"));
    mModel->setRelation(3, QSqlRelation("nationality", "nationalityId", "country"));
    mModel->select();

    mModel->setHeaderData(1, Qt::Horizontal, "Name");
    mModel->setHeaderData(2, Qt::Horizontal, "Gender");
    mModel->setHeaderData(3, Qt::Horizontal, "Nationality");
    mModel->setHeaderData(4, Qt::Horizontal, "Address");
    mModel->setHeaderData(5, Qt::Horizontal, "Phone Number");

    ui->tvTeachers->setModel(mModel);
    ui->tvTeachers->hideColumn(0); // hide id
    ui->tvTeachers->hideColumn(6); // hide photoid
    ui->tvTeachers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvTeachers->setSelectionMode(QAbstractItemView::SingleSelection);

    setupConnections();
}

PageTeachersForm::~PageTeachersForm()
{
    delete ui;
}

void PageTeachersForm::editTeacher()
{
    // check if the list view index is valid
    QModelIndex index = ui->tvTeachers->currentIndex();
    if (index.isValid())
    {
        EditTeacherDialog edit(this);

        // fetch teacher data from the database
        QString teacherId = mModel->data(mModel->index(index.row(), 0)).toString();
        Teacher teacher = DatabaseManager::instance().getTeacher(teacherId);

        // set the dialog data
        edit.setTeacher(teacher);

        if (edit.exec() == QDialog::Accepted)
        {
            qDebug() << "Saving new values to teacher";

            // get the new values from the dialog
            teacher = edit.getTeacher();

            DatabaseManager::instance().saveTeacherData(teacher, teacherId);
        }

    }
}

void PageTeachersForm::addTeacher()
{
    EditTeacherDialog add(this);
    if (add.exec() == QDialog::Accepted)
    {
        qDebug() << "Add new teacher to the database";

        Teacher teacher = add.getTeacher();
        // TODO: set photo

        // add teacher to the database
        DatabaseManager::instance().addTeacher(teacher);
    }
}

void PageTeachersForm::setupConnections()
{
    connect(ui->btnEdit, &QPushButton::clicked, this, &PageTeachersForm::editTeacher);
    connect(ui->btnAdd, &QPushButton::clicked, this, &PageTeachersForm::addTeacher);
}
