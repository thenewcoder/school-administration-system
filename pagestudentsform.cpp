#include "pagestudentsform.h"
#include "ui_pagestudentsform.h"

#include "editstudentdialog.h"
#include "databasemanager.h"
#include "student.h"
#include "genderitemdelegate.h"
#include "passworddialog.h"

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
    mModel->sort(FIELDS::NAME, Qt::AscendingOrder); // sort on the name column

    addTableHeaders();

    ui->tvStudents->setItemDelegateForColumn(FIELDS::GENDER, new GenderItemDelegate);
    ui->tvStudents->setModel(mModel);
    ui->tvStudents->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvStudents->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvStudents->hideColumn(FIELDS::ID); // hide id
    ui->tvStudents->resizeRowsToContents();

    setupConnections();
}

PageStudentsForm::~PageStudentsForm()
{
    delete ui;
}

void PageStudentsForm::setupConnections()
{
    connect(ui->btnViewStudent, &QPushButton::clicked, this, &PageStudentsForm::viewStudent);
    connect(ui->btnEdit, &QPushButton::clicked, this, &PageStudentsForm::editStudent);
    connect(ui->btnAdd, &QPushButton::clicked, this, &PageStudentsForm::addStudent);
    connect(ui->btnDelete, &QPushButton::clicked, this, &PageStudentsForm::deleteStudent);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &PageStudentsForm::updateStudentsTable);
}

void PageStudentsForm::addTableHeaders()
{
    mModel->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModel->setHeaderData(FIELDS::GRADE, Qt::Horizontal, tr("Grade"));
    mModel->setHeaderData(FIELDS::GENDER, Qt::Horizontal, tr("Gender"));
    mModel->setHeaderData(FIELDS::NATIONALITY, Qt::Horizontal, tr("Nationality"));
    mModel->setHeaderData(FIELDS::IDNUMBER, Qt::Horizontal, tr("ID Number"));
    mModel->setHeaderData(FIELDS::PHONE, Qt::Horizontal, tr("Phone Number"));
    mModel->setHeaderData(DORM, Qt::Horizontal, tr("Dormitory"));
}

void PageStudentsForm::updateStudentsTable()
{
    mModel->select();
}

void PageStudentsForm::viewStudent()
{
    // check if the index of the table view is valid
    QModelIndex index = ui->tvStudents->currentIndex();
    if (index.isValid())
    {
        // get the data of the selected student
        QString studentId = mModel->data(mModel->index(index.row(), 0)).toString();
        Student student = DatabaseManager::instance().getStudent(studentId);
        student.setId(studentId); // temporary idea

        EditStudentDialog edit(this);
        edit.setId(studentId);
        edit.setStudent(student);
        edit.setWidgetsEnabled(false); // we want view mode only

        edit.exec();
    }
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
        student.setId(studentId); // temporary idea

        EditStudentDialog edit(this);
        edit.setId(studentId);
        edit.setEditMode(true); // we want edit mode

        // set the values of the dialog
        edit.setStudent(student);

        if (edit.exec() == QDialog::Accepted)
        {
            qDebug() << "handle changes";

            student = edit.getStudent();

            // send the new data to the database manager
            DatabaseManager::instance().saveStudentData(student, studentId);

            // refresh the students table
            updateStudentsTable();

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
        updateStudentsTable();

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

            QString studentId = mModel->data(mModel->index(index.row(), 0)).toString();

            // remove the student
            DatabaseManager::instance().removeStudent(studentId);

            // refresh the student table
            updateStudentsTable();

            emit notifyStudentChanged();
        }
    }
}

void PageStudentsForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        addTableHeaders();
    }
    QWidget::changeEvent(e);
}
