#include "pageattendanceform.h"
#include "ui_pageattendanceform.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>

#include "editattendancedialog.h"
#include "databasemanager.h"
#include "classrecord.h"

PageAttendanceForm::PageAttendanceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAttendanceForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    // set up the model
    mModel->setTable("class_record_summary");
    ui->tvAttendance->setModel(mModel);
    mModel->select();

    // set up the column names
    mModel->setHeaderData(FIELDS::DATE, Qt::Horizontal, tr("Date"));
    mModel->setHeaderData(FIELDS::CLASS, Qt::Horizontal, tr("Class Name"));
    mModel->setHeaderData(FIELDS::TEACHER, Qt::Horizontal, tr("Teacher"));
    mModel->setHeaderData(FIELDS::NSTUDENT, Qt::Horizontal, tr("Total Students"));

    // setup the table view
    ui->tvAttendance->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvAttendance->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvAttendance->hideColumn(FIELDS::ID);

    setupConnections();
}

PageAttendanceForm::~PageAttendanceForm()
{
    delete ui;
}

void PageAttendanceForm::setupConnections()
{
    // refresh the table view
    connect(ui->btnRefresh, &QPushButton::clicked, this, &PageAttendanceForm::updateAttendanceTable);

    // add a new attendance record
    connect(ui->btnAdd, &QPushButton::clicked, [this] () {
        EditAttendanceDialog add(this);
        add.setWindowTitle(tr("Add a New Class Record"));
        if (add.exec() == QDialog::Accepted)
        {
            // insert a new class record into the database
            DatabaseManager::instance().addClassRecord(add.getClassRecord());

            // update the table view
            updateAttendanceTable();
        }
    });

    // edit an existing attendance record
    connect(ui->btnEdit, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvAttendance->currentIndex();
        if (index.isValid())
        {
            // get the id selected record id
            QString recordId = mModel->data(mModel->index(index.row(), 0)).toString();

            EditAttendanceDialog edit(this, true);
            edit.setWindowTitle(tr("Edit an Existing Class Record"));
            //edit.setRecordId(recordId);

            // get the record from the database
            edit.setClassRecord(DatabaseManager::instance().getClassRecord(recordId));

            if (edit.exec() == QDialog::Accepted)
            {
                // update the class record in the database
                DatabaseManager::instance().saveClassRecord(edit.getClassRecord());

                // update the table view
                updateAttendanceTable();
            }
        }
    });

    // delete an attendance record
    connect(ui->btnDelete, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvAttendance->currentIndex();
        if (index.isValid())
        {
            // make sure the user really wants to delete
            auto result = QMessageBox::warning(this, tr("Delete a class record"),
                                               tr("Are you sure you want to delete the class "
                                                  "record?\nThis action can't be undone!"),
                                               QMessageBox::Yes, QMessageBox::Cancel);
            if (result == QMessageBox::Yes)
            {
                // get id of the selected record
                QString recordId = mModel->data(mModel->index(index.row(), 0)).toString();

                // delete the record from the database
                DatabaseManager::instance().removeClassRecord(recordId);

                // update the table view
                updateAttendanceTable();
            }
        }
    });
}

void PageAttendanceForm::updateAttendanceTable()
{
    mModel->select();
}
