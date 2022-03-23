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
    connect(ui->btnAddRoom, &QPushButton::clicked, this, [this] () {
        EditOtherDialog add(tr("Add New Classroom"), this);
        if (add.exec() == QDialog::Accepted)
        {
            // add classroom to the database
            DatabaseManager::instance().addClassoom(add.name(), add.comment());
            mModelClassrooms->select();
        }
    });

    // for dormitories
    connect(ui->btnAddDorm, &QPushButton::clicked, this, [this] () {
        EditOtherDialog add(tr("Add New Dormitory"), this);
        if (add.exec() == QDialog::Accepted)
        {
            // add dormitory to the database
            DatabaseManager::instance().addDormitory(add.name(), add.comment());
            mModelDormitories->select();
        }
    });

    // for bus stops
    connect(ui->btnAddBusstop, &QPushButton::clicked, this, [this] () {
        EditOtherDialog add(tr("Add New Bus Stop"), this);
        if (add.exec() == QDialog::Accepted)
        {
            // add dormitory to the database
            DatabaseManager::instance().addBusstop(add.name(), add.comment());
            mModelBusStops->select();
        }
    });

    // for grade
    connect(ui->btnAddGrade, &QPushButton::clicked, this, [this] () {
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
    connect(ui->btnAddSubject, &QPushButton::clicked, this, [this] () {
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
    connect(ui->btnEditRoom, &QPushButton::clicked, this, [this] () {
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

                // update classroom with the new values - only refresh if update was successful
                if (DatabaseManager::instance().updateClassroom(id, edit.name(), edit.comment()))
                {
                    mModelClassrooms->select();
                    emit notifyClassroomsChanged();
                }
            }
        }
    });

    // for dormitories
    connect(ui->btnEditDorm, &QPushButton::clicked, this, [this] () {
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
                if (DatabaseManager::instance().updateDormitory(id, edit.name(), edit.comment()))
                {
                    // update the table
                    mModelDormitories->select();

                    emit notifyDormsChanged();
                }
            }
        }
    });

    // for bus stops
    connect(ui->btnEditBusstop, &QPushButton::clicked, this, [this] () {
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
                if (DatabaseManager::instance().updateBusstop(id, edit.name(), edit.comment()))
                    mModelBusStops->select();
            }
        }
    });

    // for grades
    connect(ui->btnEditGrade, &QPushButton::clicked, this, [this] () {
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
                if (DatabaseManager::instance().updateGrade(oldGrade, grade))
                {
                    // change the table row data
                    mModelGrades->setData(index, grade);

                    emit notifyGradesChanged();
                }
            }
        }
    });

    // for subjects
    connect(ui->btnEditSubject, &QPushButton::clicked, this, [this] () {
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
                if (DatabaseManager::instance().updateSubject(oldSubject, subject))
                {
                    // change the table row data
                    mModelSubjects->setData(index, subject);

                    emit notifySubjectsChanged();
                }
            }
        }
    });
}

void PageOtherForm::setupDeleteButtons()
{
    // for classrooms
    connect(ui->btnDeleteRoom, &QPushButton::clicked, this, [this] () {
        QModelIndex index = ui->tvClassrooms->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Classroom"), tr("You're about to delete a classroom.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString roomId = mModelClassrooms->data(mModelClassrooms->index(index.row(), FIELDS::ID)).toString();

                // remove the classroom
                if (DatabaseManager::instance().removeClassroom(roomId))
                {
                    // refresh the table
                    mModelClassrooms->select();

                    emit notifyClassroomsChanged();
                }
            }
        }
    });

    // for dormitories
    connect(ui->btnDeleteDorm, &QPushButton::clicked, this, [this] () {
        QModelIndex index = ui->tvDorms->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Dormitory"), tr("You're about to delete a dormitory.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString dormId = mModelDormitories->data(mModelDormitories->index(index.row(), FIELDS::ID)).toString();

                // remove the dormitory
                if (DatabaseManager::instance().removeDormitory(dormId))
                {
                    // refresh the table
                    mModelDormitories->select();

                    emit notifyDormsChanged();
                }
            }
        }
    });

    // for bus stops
    connect(ui->btnDeleteBusstop, &QPushButton::clicked, this, [this] () {
        QModelIndex index = ui->tvBusStops->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Bus stop"), tr("You're about to delete a bus stop.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString busstopId = mModelBusStops->data(mModelBusStops->index(index.row(), FIELDS::ID)).toString();

                // delete the bus stop
                if (DatabaseManager::instance().removeBusstop(busstopId))
                {
                    // refresh the table
                    mModelBusStops->select();
                }
            }
        }
    });

    // for grade list
    connect(ui->btnDeleteGrade, &QPushButton::clicked, this, [this] () {
        QModelIndex index = ui->lvGrades->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Grade"), tr("You're about to delete a grade.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString grade = mModelGrades->data(mModelGrades->index(index.row(), 0)).toString();

                // delete the grade
                if (DatabaseManager::instance().removeGrade(grade))
                {
                    // remove the row from the table
                    mModelGrades->removeRow(index.row());

                    emit notifyGradesChanged();
                }
            }
        }
    });

    // for subject list
    connect(ui->btnDeleteSubject, &QPushButton::clicked, this, [this] () {
        QModelIndex index = ui->lvSubjects->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Subject"), tr("You're about to delete a subject.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                QString subject = mModelSubjects->data(mModelSubjects->index(index.row(), 0)).toString();

                // remove the subject
                if (DatabaseManager::instance().removeSubject(subject))
                {
                    // remove the row from table
                    mModelSubjects->removeRow(index.row());

                    emit notifySubjectsChanged();
                }
            }
        }
    });
}

void PageOtherForm::setupViews()
{
    // set up the classroom table view
    mModelClassrooms->setTable("classroom");
    addClassroomTableHeaders();
    ui->tvClassrooms->setModel(mModelClassrooms);
    ui->tvClassrooms->hideColumn(FIELDS::ID); // Hide the id
    ui->tvClassrooms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvClassrooms->setSelectionMode(QAbstractItemView::SingleSelection);
    mModelClassrooms->select();
    ui->tvClassrooms->horizontalHeader()->setStretchLastSection(true);

    // set up the dormitory table view
    mModelDormitories->setTable("dormitory");
    addDormitoryTableHeaders();
    ui->tvDorms->setModel(mModelDormitories);
    ui->tvDorms->hideColumn(FIELDS::ID); // Hide the id
    ui->tvDorms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvDorms->setSelectionMode(QAbstractItemView::SingleSelection);
    mModelDormitories->select();
    ui->tvDorms->horizontalHeader()->setStretchLastSection(true);

    // set up the bus stop table view
    mModelBusStops->setTable("bus_stop");
    addBusstopTableHeaders();
    ui->tvBusStops->setModel(mModelBusStops);
    ui->tvBusStops->hideColumn(FIELDS::ID); // Hide the id
    ui->tvBusStops->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvBusStops->setSelectionMode(QAbstractItemView::SingleSelection);
    mModelBusStops->select();
    ui->tvBusStops->horizontalHeader()->setStretchLastSection(true);

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

void PageOtherForm::addClassroomTableHeaders()
{
    mModelClassrooms->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModelClassrooms->setHeaderData(FIELDS::COMMENT, Qt::Horizontal, tr("Comment"));
}

void PageOtherForm::addDormitoryTableHeaders()
{
    mModelDormitories->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModelDormitories->setHeaderData(FIELDS::COMMENT, Qt::Horizontal, tr("Comment"));
}

void PageOtherForm::addBusstopTableHeaders()
{
    mModelBusStops->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Name"));
    mModelBusStops->setHeaderData(FIELDS::COMMENT, Qt::Horizontal, tr("Comment"));
}

void PageOtherForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        addClassroomTableHeaders();
        addDormitoryTableHeaders();
        addBusstopTableHeaders();
    }
    QWidget::changeEvent(e);
}
