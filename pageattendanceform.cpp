#include "pageattendanceform.h"
#include "ui_pageattendanceform.h"

#include <QSqlTableModel>

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
    connect(ui->btnRefresh, &QPushButton::clicked, [this] () {
        mModel->select();
    });

    connect(ui->btnAdd, &QPushButton::clicked, [this] () {
        EditAttendanceDialog add(this);
        add.setWindowTitle(tr("Add a New Class Record"));
        if (add.exec() == QDialog::Accepted)
        {
            // add the class record to the database
            DatabaseManager::instance().addClassRecord(add.getClassRecord());

            // update the table view
            mModel->select();
        }
    });

    connect(ui->btnEdit, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvAttendance->currentIndex();
        if (index.isValid())
        {
            // get the id selected record id
            QString recordId = mModel->data(mModel->index(index.row(), 0)).toString();

            EditAttendanceDialog edit(this);
            edit.setWindowTitle(tr("Edit an Existing Class Record"));

            // get the record from the database
            edit.setClassRecord(DatabaseManager::instance().getClassRecord(recordId));

            if (edit.exec() == QDialog::Accepted)
            {
                // update the record in the database
                DatabaseManager::instance().saveClassRecord(edit.getClassRecord());

                // update the table view
                mModel->select();
            }
        }
    });

    connect(ui->btnDelete, &QPushButton::clicked, [this] () {

    });
}
