#include "pageotherform.h"
#include "ui_pageotherform.h"

#include <QStringListModel>
#include <QSqlTableModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

#include "databasemanager.h"
#include "editotherdialog.h"

PageOtherForm::PageOtherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageOtherForm),
    mModelClassrooms(new QSqlTableModel(this)),
    mModelDormitories(new QSqlTableModel(this)),
    mModelBusStops(new QSqlTableModel(this)),
    mModelGrades(new QStringListModel(this)),
    mModelSubjects(new QStringListModel(this))
{
    ui->setupUi(this);

    // set the first tab as active on startup
    ui->tabWidget->setCurrentWidget(ui->tabRooms);

    // setup the table views for all the tabs
    setupViews();

    setupConnections();

}

PageOtherForm::~PageOtherForm()
{
    delete ui;
}

void PageOtherForm::setupConnections()
{
    setupAddButtons();
    setupEditButtons();
    setupDeleteButtons();
}

void PageOtherForm::setupAddButtons()
{
    // for classrooms
    connect(ui->btnAddRoom, &QPushButton::clicked, [this] () {
        EditOtherDialog add(tr("Add New Classroom"), this);
        if (add.exec() == QDialog::Accepted)
        {
            // add classroom to the database
            DatabaseManager::instance().addClassoom(add.name(), add.comment());
            mModelClassrooms->select();
        }
    });

    // for dormitories
    connect(ui->btnAddDorm, &QPushButton::clicked, [this] () {
        EditOtherDialog add(tr("Add New Dormitory"), this);
        if (add.exec() == QDialog::Accepted)
        {
            // add dormitory to the database
            DatabaseManager::instance().addDormitory(add.name(), add.comment());
            mModelDormitories->select();
        }
    });

    // for bus stops
    connect(ui->btnAddBusstop, &QPushButton::clicked, [this] () {
        EditOtherDialog add(tr("Add New Bus Stop"), this);
        if (add.exec() == QDialog::Accepted)
        {
            // add dormitory to the database
            DatabaseManager::instance().addBusstop(add.name(), add.comment());
            mModelBusStops->select();
        }
    });

    // for grade
    connect(ui->btnAddGrade, &QPushButton::clicked, [this] () {
        QString grade = QInputDialog::getText(this,
                                              tr("Add New Grade"),
                                              tr("Grade name:"));
        if (!grade.isEmpty())
        {
            // add grade to database - any better way?
            DatabaseManager::instance().addGrade(grade);
            QStringList grades = DatabaseManager::instance().grades();
            mModelGrades->setStringList(grades);
            mModelGrades->sort(0);
        }
    });

    // for subject
    connect(ui->btnAddSubject, &QPushButton::clicked, [this] () {
        QString subject = QInputDialog::getText(this,
                                                tr("Add New Subject"),
                                                tr("Subject name:"));
        if (!subject.isEmpty())
        {
            // add subject to database
            DatabaseManager::instance().addSubject(subject);
            QStringList subjects = DatabaseManager::instance().subjects();
            mModelSubjects->setStringList(subjects);
            mModelSubjects->sort(0);
        }
    });
}

void PageOtherForm::setupEditButtons()
{
    // for classroom
    connect(ui->btnEditRoom, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvClassrooms->currentIndex();
        if (index.isValid())
        {
            EditOtherDialog edit(tr("Edit Classroom"), this);

            QString name = mModelClassrooms->data(mModelClassrooms->index(index.row(), 1)).toString();
            QString comment = mModelClassrooms->data(mModelClassrooms->index(index.row(), 2)).toString();

            edit.setName(name);
            edit.setComment(comment);

            if (edit.exec() == QDialog::Accepted)
            {
                // get the id of the selected classroom row
                QString id = mModelClassrooms->data(mModelClassrooms->index(index.row(), 0)).toString();

                // update classroom with the new values
                DatabaseManager::instance().updateClassroom(id, edit.name(), edit.comment());
                mModelClassrooms->select();
            }
        }
    });

    // for dormitories
    connect(ui->btnEditDorm, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvDorms->currentIndex();
        if (index.isValid())
        {
            EditOtherDialog edit(tr("Edit Dormitory"), this);

            QString name = mModelDormitories->data(mModelDormitories->index(index.row(), 1)).toString();
            QString comment = mModelDormitories->data(mModelDormitories->index(index.row(), 2)).toString();

            edit.setName(name);
            edit.setComment(comment);

            if (edit.exec() == QDialog::Accepted)
            {
                // get the id of the selected dormitory row
                QString id = mModelDormitories->data(mModelDormitories->index(index.row(), 0)).toString();

                // update dormitory with the new values
                DatabaseManager::instance().updateDormitory(id, edit.name(), edit.comment());
                mModelDormitories->select();
            }
        }
    });

    // for bus stops
    connect(ui->btnEditBusstop, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvBusStops->currentIndex();
        if (index.isValid())
        {
            EditOtherDialog edit(tr("Edit Bus Stop"), this);

            QString name = mModelBusStops->data(mModelBusStops->index(index.row(), 1)).toString();
            QString comment = mModelBusStops->data(mModelBusStops->index(index.row(), 2)).toString();

            edit.setName(name);
            edit.setComment(comment);

            if (edit.exec() == QDialog::Accepted)
            {
                // get the id of the selected bus stop row
                QString id = mModelBusStops->data(mModelBusStops->index(index.row(), 0)).toString();

                // update bus_stop with the new values
                DatabaseManager::instance().updateBusstop(id, edit.name(), edit.comment());
                mModelBusStops->select();
            }
        }
    });

    // for grades
    connect(ui->btnEditGrade, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->lvGrades->currentIndex();
        if (index.isValid())
        {
            QString oldGrade = mModelGrades->data(mModelGrades->index(index.row(), 0)).toString();
            bool ok;
            QString grade = QInputDialog::getText(this,
                                                  tr("Edit Grade"),
                                                  tr("New Grade Name"),
                                                  QLineEdit::Normal,
                                                  oldGrade,
                                                  &ok);
            if (!grade.isEmpty() && ok)
            {
                // update the grade in the database
                DatabaseManager::instance().updateGrade(oldGrade, grade);

                // change the table row data
                mModelGrades->setData(index, grade);
            }
        }
    });

    // for subjects
    connect(ui->btnEditSubject, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->lvSubjects->currentIndex();
        if (index.isValid())
        {
            QString oldSubject = mModelSubjects->data(mModelSubjects->index(index.row(), 0)).toString();
            bool ok;
            QString subject = QInputDialog::getText(this,
                                                  tr("Edit Grade"),
                                                  tr("New Subject Name"),
                                                  QLineEdit::Normal,
                                                  oldSubject,
                                                  &ok);
            if (!subject.isEmpty() && ok)
            {
                // first remove the selection - any better way?
                DatabaseManager::instance().updateSubject(oldSubject, subject);

                // change the table row data
                mModelSubjects->setData(index, subject);
            }
        }
    });
}

void PageOtherForm::setupDeleteButtons()
{
    // for classrooms
    connect(ui->btnDeleteRoom, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvClassrooms->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Classroom"), tr("You're about to delete a classroom.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                mModelClassrooms->removeRow(index.row());
                mModelClassrooms->select();
            }
        }
    });

    // for dormitories
    connect(ui->btnDeleteDorm, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvDorms->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Dormitory"), tr("You're about to delete a dormitory.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                mModelDormitories->removeRow(index.row());
                mModelDormitories->select();
            }
        }
    });

    // for bus stops
    connect(ui->btnDeleteBusstop, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvBusStops->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Bus stop"), tr("You're about to delete a bus stop.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                mModelBusStops->removeRow(index.row());
                mModelBusStops->select();
            }
        }
    });

    // for grade list
    connect(ui->btnDeleteGrade, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->lvGrades->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Grade"), tr("You're about to delete a grade.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString grade = mModelGrades->data(mModelGrades->index(index.row(), 0)).toString();
                DatabaseManager::instance().removeGrade(grade);
                mModelGrades->removeRow(index.row());
            }
        }
    });

    // for subject list
    connect(ui->btnDeleteSubject, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->lvSubjects->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Subject"), tr("You're about to delete a subject.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString subject = mModelSubjects->data(mModelSubjects->index(index.row(), 0)).toString();
                DatabaseManager::instance().removeSubject(subject);
                mModelSubjects->removeRow(index.row());
            }
        }
    });
}

void PageOtherForm::setupViews()
{
    // set up the classroom table view
    mModelClassrooms->setTable("classroom");
    mModelClassrooms->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModelClassrooms->setHeaderData(FIELDS::COMMENT, Qt::Horizontal, tr("Comment"));
    ui->tvClassrooms->setModel(mModelClassrooms);
    ui->tvClassrooms->hideColumn(FIELDS::ID); // Hide the id
    ui->tvClassrooms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvClassrooms->setSelectionMode(QAbstractItemView::SingleSelection);
    mModelClassrooms->select();
    ui->tvClassrooms->resizeColumnsToContents();

    // set up the dormitory table view
    mModelDormitories->setTable("dormitory");
    mModelDormitories->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModelDormitories->setHeaderData(FIELDS::COMMENT, Qt::Horizontal, tr("Comment"));
    ui->tvDorms->setModel(mModelDormitories);
    ui->tvDorms->hideColumn(FIELDS::ID); // Hide the id
    ui->tvDorms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvDorms->setSelectionMode(QAbstractItemView::SingleSelection);
    mModelDormitories->select();
    ui->tvDorms->resizeColumnsToContents();

    // set up the bus stop table view
    mModelBusStops->setTable("bus_stop");
    mModelBusStops->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModelBusStops->setHeaderData(FIELDS::COMMENT, Qt::Horizontal, tr("Comment"));
    ui->tvBusStops->setModel(mModelBusStops);
    ui->tvBusStops->hideColumn(FIELDS::ID); // Hide the id
    ui->tvBusStops->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvBusStops->setSelectionMode(QAbstractItemView::SingleSelection);
    mModelBusStops->select();
    ui->tvBusStops->resizeColumnsToContents();

    // set up the grade list view
    QStringList grades = DatabaseManager::instance().grades();
    mModelGrades->setStringList(grades);
    ui->lvGrades->setModel(mModelGrades);
    ui->lvGrades->model()->sort(0);

    // set up the subjects list view
    QStringList subjects = DatabaseManager::instance().subjects();
    mModelSubjects->setStringList(subjects);
    ui->lvSubjects->setModel(mModelSubjects);
    ui->lvSubjects->model()->sort(0);
}
