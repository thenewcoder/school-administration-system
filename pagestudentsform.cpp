#include "pagestudentsform.h"
#include "ui_pagestudentsform.h"

#include "editstudentdialog.h"
#include "databasemanager.h"
#include "student.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

PageStudentsForm::PageStudentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageStudentsForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("student_summary");
    mModel->select();

    mModel->setHeaderData(1, Qt::Horizontal, "Name");
    mModel->setHeaderData(2, Qt::Horizontal, "Gender");
    mModel->setHeaderData(3, Qt::Horizontal, "Nationality");
    mModel->setHeaderData(4, Qt::Horizontal, "ID Number");
    mModel->setHeaderData(5, Qt::Horizontal, "Phone Number");
    mModel->setHeaderData(6, Qt::Horizontal, "Dormitory");

    ui->tvStudents->setModel(mModel);
    ui->tvStudents->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvStudents->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvStudents->hideColumn(0); // hide id
    ui->tvStudents->resizeRowsToContents();

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

    connect(ui->btnDelete, &QPushButton::clicked, this, &PageStudentsForm::deleteStudent);
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

            emit notifyStudentChanged();
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

        emit notifyStudentChanged();
    }
}

void PageStudentsForm::deleteStudent()
{
    // get index of selected row
    QModelIndex index = ui->tvStudents->currentIndex();
    if (index.isValid())
    {
        // warn the user about destructive action
        int reply = QMessageBox::warning(this, tr("Delete Student"),
                             tr("Are you sure you want to delete?\nThis cannot be undone!"),
                             QMessageBox::Ok, QMessageBox::Cancel);

        if (reply == QMessageBox::Ok)
        {
            QString studentId = mModel->data(mModel->index(index.row(), 0)).toString();

            // remove the student
            DatabaseManager::instance().removeStudent(studentId);

            // refresh the student table
            mModel->select();

            emit notifyStudentChanged();
        }
    }
}

