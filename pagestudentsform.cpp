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
        edit.setName(student.name());
        //edit.setDateOfBirth(student.dateOfBirth());
        edit.setGender(student.gender());
        edit.setNationality(student.nationality());
        edit.setPassportNumber(student.passportNumber());
        edit.setIdNumber(student.iDNumber());
        edit.setAddress(student.address());
        edit.setStudentPhoneNumber(student.studentPhoneNumber());
        edit.setStudentEmail(student.studentEmail());
        edit.setFathersPhoneNumber(student.fathersPhoneNumber());
        edit.setMothersPhoneNumber(student.mothersPhoneNumber());
        edit.setParentEmail(student.parentsEmail());

        if (edit.exec() == QDialog::Accepted)
        {
            qDebug() << "handle changes";

            student.setName(edit.name());
            //student.setDateOfBirth(edit.dateOfBirth());
            student.setGender(edit.gender());
            student.setNationality(edit.nationality());
            student.setPassportNumber(edit.passportNumber());
            student.setIDNumber(edit.idNumber());
            student.setAddress(edit.address());
            student.setStudentPhoneNumber(edit.studentPhoneNumber());
            student.setStudentEmail(edit.studentEmail());
            student.setFathersPhoneNumber(edit.fathersPhoneNumber());
            student.setMothersPhoneNumber(edit.mothersPhoneNumber());
            student.setParentsEmail(edit.parentEmail());

            // send the new data to the database manager
            DatabaseManager::instance().saveStudentData(student, studentId);
        }
    }


}

void PageStudentsForm::addStudent()
{
    EditStudentDialog add(this);
    if (add.exec() == QDialog::Accepted)
    {
        qDebug() << "add new student";

        Student student;
        student.setName(add.name());
        // TODO: fix date of birth type missmatch
        //student.setDateOfBirth(add.dateOfBirth());
        student.setGender(add.gender());
        student.setNationality(add.nationality());
        student.setPassportNumber(add.passportNumber());
        student.setIDNumber(add.idNumber());
        student.setAddress(add.address());
        student.setStudentPhoneNumber(add.studentPhoneNumber());
        student.setStudentEmail(add.studentEmail());
        student.setFathersPhoneNumber(add.fathersPhoneNumber());
        student.setMothersPhoneNumber(add.mothersPhoneNumber());
        student.setParentsEmail(add.parentEmail());

        DatabaseManager::instance().addStudent(student);
    }
}

