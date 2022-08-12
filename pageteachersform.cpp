#include "pageteachersform.h"
#include "ui_pageteachersform.h"

#include "databasemanager.h"
#include "editteacherdialog.h"
#include "teacher.h"
#include "genderitemdelegate.h"
#include "passworddialog.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>
#include <QTableView>

PageTeachersForm::PageTeachersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTeachersForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("teacher_summary2"); // maybe temporary
    mModel->select();
    mModel->sort(FIELDS::NAME, Qt::AscendingOrder); // sort by the name column

    addTableHeaders();

    ui->tvTeachers->setModel(mModel);
    ui->tvTeachers->setItemDelegateForColumn(FIELDS::GENDER, new GenderItemDelegate);
    ui->tvTeachers->hideColumn(FIELDS::ID); // hide id
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
        edit.setEditMode(true); // make sure we get edit mode behaviour

        if (edit.exec() == QDialog::Accepted)
        {
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
            // force user to enter password before processing delete of user
            PasswordDialog passDialog(this);

            if (passDialog.exec() == QDialog::Rejected)
                return;

            // validate password
            if (!passDialog.isAuthenticated())
            {
                QMessageBox::critical(this, tr("Wrong Password"), tr("You entered the wrong password!"));
                return;
            }

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
    ui->tvTeachers->resizeRowsToContents(); // not sure if needed
}

void PageTeachersForm::viewTeacher()
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
        edit.setWidgetsEnabled(false); // make sure we get view mode behaviour

        edit.exec();
    }
}

void PageTeachersForm::setupConnections()
{
    connect(ui->btnViewTeacher, &QPushButton::clicked, this, &PageTeachersForm::viewTeacher);
    connect(ui->btnEdit, &QPushButton::clicked, this, &PageTeachersForm::editTeacher);
    connect(ui->btnAdd, &QPushButton::clicked, this, &PageTeachersForm::addTeacher);
    connect(ui->btnDelete, &QPushButton::clicked, this, &PageTeachersForm::deleteTeacher);
    connect(ui->btnRefresh, &QPushButton::clicked, mModel, &QSqlTableModel::select);
}

void PageTeachersForm::addTableHeaders()
{
    mModel->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModel->setHeaderData(FIELDS::GENDER, Qt::Horizontal, tr("Gender"));
    mModel->setHeaderData(FIELDS::NATIONALITY, Qt::Horizontal, tr("Nationality"));
    mModel->setHeaderData(FIELDS::PREFERRED_NAME, Qt::Horizontal, tr("Preferred Name"));
    mModel->setHeaderData(FIELDS::PHONE, Qt::Horizontal, tr("Phone Number"));
    mModel->setHeaderData(FIELDS::CLASSES, Qt::Horizontal, tr("Classes"));  // maybe temporary
}

void PageTeachersForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        addTableHeaders();
    }
    QWidget::changeEvent(e);
}
