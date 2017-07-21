#include "pagestudentsform.h"
#include "ui_pagestudentsform.h"

#include "editstudentdialog.h"
#include "databasemanager.h"
#include "student.h"

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
    ui->tvStudents->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvStudents->setSelectionMode(QAbstractItemView::SingleSelection);
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
    // check if the index of the table view is valid
    QModelIndex index = ui->tvStudents->currentIndex();
    if (index.isValid())
    {
        // get the data of the selected student
        QString studentId = mModel->data(mModel->index(index.row(), 0)).toString();
        Student student = DatabaseManager::instance().getStudent(studentId);

        EditStudentDialog edit(this);

        // set the values of the dialog
        edit.setStudent(student);

        if (edit.exec() == QDialog::Accepted)
        {
            qDebug() << "handle changes";

            student = edit.getStudent();

            // send the new data to the database manager
            DatabaseManager::instance().saveStudentData(student, studentId);

            // refresh the students table
            mModel->select();
        }
    }


}

void PageStudentsForm::addStudent()
{
    EditStudentDialog add(this);
    if (add.exec() == QDialog::Accepted)
    {
        qDebug() << "add new student";

        Student student = add.getStudent();

        DatabaseManager::instance().addStudent(student);

        // refresh the students table
        mModel->select();
    }
}

