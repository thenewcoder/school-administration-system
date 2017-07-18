#include "pageteachersform.h"
#include "ui_pageteachersform.h"

#include "editteacherdialog.h"

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

    setupConnections();
}

PageTeachersForm::~PageTeachersForm()
{
    delete ui;
}

void PageTeachersForm::editTeacher()
{
    EditTeacherDialog edit(this);
    if (edit.exec() == QDialog::Accepted)
    {
        qDebug() << "Saving new values to teacher";
    }
}

void PageTeachersForm::setupConnections()
{
    connect(ui->btnEdit, &QPushButton::clicked, this, &PageTeachersForm::editTeacher);
}
