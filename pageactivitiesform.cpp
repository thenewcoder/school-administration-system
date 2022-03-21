#include "pageactivitiesform.h"
#include "ui_pageactivitiesform.h"

#include <QSqlTableModel>
#include <QMessageBox>
#include "editactivitydialog.h"
#include "databasemanager.h"
#include "activity.h"

PageActivitiesForm::PageActivitiesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageActivitiesForm),
    mModelSports(new QSqlTableModel(this)),
    mModelActivities(new QSqlTableModel(this))
{
    ui->setupUi(this);

    initTables();
    setupConnections();
}

PageActivitiesForm::~PageActivitiesForm()
{
    delete ui;
}

void PageActivitiesForm::setupConnections()
{
    setupRefreshButtons();
    setupAddButtons();
    setupEditButtons();
    setupDeleteButtons();
}

void PageActivitiesForm::initTables()
{
    // prepare the sports table view
    mModelSports->setTable("sports_summary");
    mModelSports->select();
    addSportsTableHeaders();
    ui->tvSports->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvSports->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvSports->setModel(mModelSports);
    ui->tvSports->hideColumn(FIELDS::ID);

    //prepare the after-school activities table view
    mModelActivities->setTable("activity_summary");
    mModelActivities->select();
    addActivityTableHeaders();
    ui->tvAfterSchool->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvAfterSchool->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvAfterSchool->setModel(mModelActivities);
    ui->tvAfterSchool->hideColumn(FIELDS::ID);
}

void PageActivitiesForm::setupRefreshButtons()
{
    connect(ui->btnRefreshSports, &QPushButton::clicked, this, &PageActivitiesForm::updateSportsTable);

    connect(ui->btnRefreshAfterSchool, &QPushButton::clicked, this, &PageActivitiesForm::updateAfterSchoolTable);
}

void PageActivitiesForm::setupAddButtons()
{
    // add a new sport
    connect(ui->btnAddSports, &QPushButton::clicked, [this] () {
        EditActivityDialog add(this, tr("Add a New Sports Activity"));

        if (add.exec() == QDialog::Accepted)
        {
            // add the activity to the database
            Activity activity = add.getActivity();
            activity.setType(Activity::TYPE::SPORTS);
            DatabaseManager::instance().addActivity(activity);

            // update the table view
            updateSportsTable();
        }
    });

    // add a new after school activity
    connect(ui->btnAddAfterSchool, &QPushButton::clicked, [this] () {
        EditActivityDialog add(this, tr("Add a New After-School Activity"));

        if (add.exec() == QDialog::Accepted)
        {
            // add the after school activity to the database
            Activity activity = add.getActivity();
            activity.setType(Activity::TYPE::AFTER_SCHOOL);
            DatabaseManager::instance().addActivity(activity);

            // update the table view
            updateAfterSchoolTable();
        }
    });
}

void PageActivitiesForm::setupEditButtons()
{
    // edit an existing sport
    connect(ui->btnEditSports, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvSports->currentIndex();
        if (index.isValid())
        {
            // get the activity id
            QString id = mModelSports->data(mModelSports->index(index.row(), 0)).toString();

            // get the activity data from the database
            Activity activity = DatabaseManager::instance().getActivity(id);

            // prepare the edit dialog
            EditActivityDialog edit(this, tr("Edit a Sports Activity"), true);
            edit.setActivity(activity);

            if (edit.exec() == QDialog::Accepted)
            {
                // update the activity in the database
                activity = edit.getActivity();
                activity.setType(Activity::TYPE::SPORTS);
                activity.setId(id);
                DatabaseManager::instance().saveActivityData(activity);

                // update the sports table view
                updateSportsTable();
            }
        }
    });

    // edit an after school activity
    connect(ui->btnEditAfterSchool, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvAfterSchool->currentIndex();
        if (index.isValid())
        {
            // get the activity id
            QString id = mModelActivities->data(mModelActivities->index(index.row(), 0)).toString();

            // get the activity data from the database
            Activity activity = DatabaseManager::instance().getActivity(id);

            // prepare the edit dialog
            EditActivityDialog edit(this, tr("Edit an After-School Activity"), true);
            edit.setActivity(activity);

            if (edit.exec() == QDialog::Accepted)
            {
                // update the activity in the database
                activity = edit.getActivity();
                activity.setType(Activity::TYPE::AFTER_SCHOOL);
                activity.setId(id);
                DatabaseManager::instance().saveActivityData(activity);

                // update the after school table view
                updateAfterSchoolTable();
            }
        }
    });
}

void PageActivitiesForm::setupDeleteButtons()
{
    // delete a sport
    connect(ui->btnDeleteSports, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvSports->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Activity"), tr("You're about to delete an activity.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                // get the activity id
                QString id = mModelSports->data(mModelSports->index(index.row(), 0)).toString();

                // remove the activity from the database
                DatabaseManager::instance().removeActivity(id);

                // update the table view content
                updateSportsTable();
            }
        }
    });

    // delete an after school activity
    connect(ui->btnDeleteAfterSchool, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->tvAfterSchool->currentIndex();
        if (index.isValid())
        {
            int result = QMessageBox::warning(this, tr("Delete Activity"), tr("You're about to delete an activity.\n"
                                                                            "This can't be undone. Are you sure?"),
                                              QMessageBox::Ok | QMessageBox::Cancel);
            if (result == QMessageBox::Ok)
            {
                // get the activity id
                QString id = mModelActivities->data(mModelActivities->index(index.row(), 0)).toString();

                // remove the activity from the database
                DatabaseManager::instance().removeActivity(id);

                // update the table view content
                updateAfterSchoolTable();
            }
        }
    });
}

void PageActivitiesForm::addSportsTableHeaders()
{
    mModelSports->setHeaderData(FIELDS::CODE, Qt::Horizontal, tr("Code"));
    mModelSports->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Sport Name"));
    mModelSports->setHeaderData(FIELDS::TEACHER, Qt::Horizontal, tr("Teacher Advisor"));
    mModelSports->setHeaderData(FIELDS::LIMIT, Qt::Horizontal, tr("Membership"));
}

void PageActivitiesForm::addActivityTableHeaders()
{
    mModelActivities->setHeaderData(FIELDS::CODE, Qt::Horizontal, tr("Code"));
    mModelActivities->setHeaderData(FIELDS::NAME, Qt::Horizontal, tr("Activity Name"));
    mModelActivities->setHeaderData(FIELDS::TEACHER, Qt::Horizontal, tr("Teacher Advisor"));
    mModelActivities->setHeaderData(FIELDS::LIMIT, Qt::Horizontal, tr("Membership"));
}

void PageActivitiesForm::updateSportsTable()
{
    mModelSports->select();
}

void PageActivitiesForm::updateAfterSchoolTable()
{
    mModelActivities->select();
}

void PageActivitiesForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        addSportsTableHeaders();
        addActivityTableHeaders();
    }
    QWidget::changeEvent(e);
}
