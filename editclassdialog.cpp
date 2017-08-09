﻿#include "editclassdialog.h"
#include "ui_editclassdialog.h"

#include <QStringListModel>
#include "class.h"
#include "databasemanager.h"
#include "selectordialog.h"

#include <QDebug>

EditClassDialog::EditClassDialog(const QString &title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditClassDialog),
    mModelTeachers(new QStringListModel(this)),
    mModelStudents(new QStringListModel(this))
{
    ui->setupUi(this);

    // set the title for the dialog
    setWindowTitle(title);

    // set up the models for the list views
    ui->lvTeachers->setModel(mModelTeachers);
    ui->lvStudents->setModel(mModelStudents);

    // set up the subjects combo box
    QStringList subs = DatabaseManager::instance().subjects();
    ui->cbSubject->setModel(new QStringListModel(subs));
    ui->cbSubject->model()->sort(0);

    // set up the classrooms combo box
    QStringList rooms = DatabaseManager::instance().classrooms();
    ui->cbClassroom->setModel(new QStringListModel(rooms));

    setupConnections();
}

EditClassDialog::~EditClassDialog()
{
    delete ui;
}

QString EditClassDialog::className() const
{
    return ui->leClassName->text();
}

void EditClassDialog::setClassname(const QString &name)
{
    ui->leClassName->setText(name);
}

QString EditClassDialog::subject() const
{
    return ui->cbSubject->currentText();
}

void EditClassDialog::setSubject(const QString &subject)
{
    ui->cbSubject->setCurrentText(subject);
}

QString EditClassDialog::classroom() const
{
    return ui->cbClassroom->currentText();
}

void EditClassDialog::setClassroom(const QString &room)
{
    ui->cbClassroom->setCurrentText(room);
}

QStringList EditClassDialog::teachers() const
{
    return mModelTeachers->stringList();
}

void EditClassDialog::setTeachers(const QStringList &teachers)
{
    mModelTeachers->setStringList(teachers);
    mModelTeachers->sort(0);
}

QStringList EditClassDialog::students() const
{
    return mModelStudents->stringList();
}

void EditClassDialog::setStudents(const QStringList &students)
{
    mModelStudents->setStringList(students);
    mModelStudents->sort(0);
}

void EditClassDialog::setClass(const Class &c)
{
    setClassname(c.className());
    setSubject(c.subject());
    setClassroom(c.classRoom());
    setTeachers(c.teachers());
    setStudents(c.students());
}

Class EditClassDialog::getClass() const
{
    Class c;
    c.setClassname(className());
    c.setSubject(subject());
    c.setClassroom(classroom());
    c.setTeachers(teachers());
    c.setStudents(students());
    return c;
}

void EditClassDialog::setupConnections()
{
    connect(ui->btnEditTeachers, &QPushButton::clicked, [this] () {
        SelectorDialog edit("Edit Teachers",
                            DatabaseManager::instance().teachers(),
                            teachers(), this);

        if (edit.exec() == QDialog::Accepted)
        {
            // set the new teachers string list
            setTeachers(edit.getItems());
        }
    });

    connect(ui->btnEditStudents, &QPushButton::clicked, [this] () {
        SelectorDialog edit("Edit Students",
                            DatabaseManager::instance().students(),
                            students(), this);

        if (edit.exec() == QDialog::Accepted)
        {
            // set the new students string list
            setStudents(edit.getItems());
        }
    });
}
