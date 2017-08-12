#include "pageteachersform.h"
#include "ui_pageteachersform.h"

#include "databasemanager.h"
#include "editteacherdialog.h"
#include "teacher.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

PageTeachersForm::PageTeachersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTeachersForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("teacher_summary2"); // maybe temporary
    mModel->select();

    mModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    mModel->setHeaderData(2, Qt::Horizontal, tr("Gender"));
    mModel->setHeaderData(3, Qt::Horizontal, tr("Nationality"));
    mModel->setHeaderData(4, Qt::Horizontal, tr("Address"));
    mModel->setHeaderData(5, Qt::Horizontal, tr("Phone Number"));
    mModel->setHeaderData(6, Qt::Horizontal, tr("Classes"));  // maybe temporary

    ui->tvTeachers->setModel(mModel);
    ui->tvTeachers->hideColumn(0); // hide id
    ui->tvTeachers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvTeachers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvTeachers->resizeRowsToContents();

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
        // fetch teacher data from the database
        QString teacherId = mModel->data(mModel->index(index.row(), 0)).toString();
        Teacher teacher = DatabaseManager::instance().getTeacher(teacherId);
        teacher.setId(teacherId);

        // set the dialog data
        EditTeacherDialog edit(this);
        edit.setId(teacherId);
        edit.setTeacher(teacher);

        if (edit.exec() == QDialog::Accepted)
        {
            qDebug() << "Saving new values to teacher";

            // get the new values from the dialog
            teacher = edit.getTeacher();

            DatabaseManager::instance().saveTeacherData(teacher, teacherId);

            // refresh the teachers table
            updateTeacherTable();

            emit notifyTeacherChanged();
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

        // add teacher to the database
        DatabaseManager::instance().addTeacher(teacher);

        // update the teachers table
        updateTeacherTable();

        emit notifyTeacherChanged();
    }
}

void PageTeachersForm::deleteTeacher()
{
    // get index of selected row
    QModelIndex index = ui->tvTeachers->currentIndex();
    if (index.isValid())
    {
        // warn the user about destructive action
        int reply = QMessageBox::warning(this, tr("Delete Teacher"),
                             tr("Are you sure you want to delete?\nThis cannot be undone!"),
                             QMessageBox::Ok, QMessageBox::Cancel);

        if (reply == QMessageBox::Ok)
        {
            QString teacherId = mModel->data(mModel->index(index.row(), 0)).toString();

            // remove the teacher
            DatabaseManager::instance().removeTeacher(teacherId);

            // refresh the teacher table
            updateTeacherTable();

            emit notifyTeacherChanged();
        }
    }
}

void PageTeachersForm::updateTeacherTable()
{
    mModel->select();
}

void PageTeachersForm::setupConnections()
{
    connect(ui->btnEdit, &QPushButton::clicked, this, &PageTeachersForm::editTeacher);
    connect(ui->btnAdd, &QPushButton::clicked, this, &PageTeachersForm::addTeacher);
    connect(ui->btnDelete, &QPushButton::clicked, this, &PageTeachersForm::deleteTeacher);
    connect(ui->btnRefresh, &QPushButton::clicked, mModel, &QSqlTableModel::select);
}
