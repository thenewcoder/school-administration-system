#include "pagestudentsform.h"
#include "ui_pagestudentsform.h"

#include "editstudentdialog.h"

#include <QSqlRelationalTableModel>
#include <QDebug>

PageStudentsForm::PageStudentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageStudentsForm),
    mModel(new QSqlRelationalTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("student");
    mModel->setRelation(3, QSqlRelation("gender", "genderId", "type"));
    mModel->setRelation(4, QSqlRelation("nationality", "nationalityId", "country"));

    mModel->select();

    ui->tvStudents->setModel(mModel);
    ui->tvStudents->hideColumn(0); // hide id

    setupConnections();
}

PageStudentsForm::~PageStudentsForm()
{
    delete ui;
}

void PageStudentsForm::setupConnections()
{
    connect(ui->btnEdit, &QPushButton::clicked, this, &PageStudentsForm::editStudent);

    connect(ui->btnAdd, &QPushButton::clicked, this, &PageStudentsForm::addStudent);
}

void PageStudentsForm::editStudent()
{
    EditStudentDialog edit(this);
    if (edit.exec() == QDialog::Accepted)
    {
        qDebug() << "handle changes";
    }
}

void PageStudentsForm::addStudent()
{
    EditStudentDialog add(this);
    if (add.exec() == QDialog::Accepted)
    {
        qDebug() << "add new student";
    }
}

