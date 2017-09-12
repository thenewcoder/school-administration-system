#include "pageactivitiesform.h"
#include "ui_pageactivitiesform.h"

#include <QSqlTableModel>

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

}

void PageActivitiesForm::initTables()
{
    // prepare the sports table view
    mModelSports->setHeaderData(1, Qt::Horizontal, tr("Code"));
    mModelSports->setHeaderData(2, Qt::Horizontal, tr("Sport Name"));
    mModelSports->setHeaderData(3, Qt::Horizontal, tr("Teacher Advisor"));
    mModelSports->setHeaderData(4, Qt::Horizontal, tr("Membership"));

    ui->tvSports->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvSports->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tvSports->setModel(mModelSports);


    //prepare the after-school activities table view
    mModelActivities->setHeaderData(1, Qt::Horizontal, tr("Code"));
    mModelActivities->setHeaderData(2, Qt::Horizontal, tr("Activity Name"));
    mModelActivities->setHeaderData(3, Qt::Horizontal, tr("Teacher Advisor"));
    mModelActivities->setHeaderData(4, Qt::Horizontal, tr("Membership"));

    ui->tvAfterSchool->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvAfterSchool->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tvAfterSchool->setModel(mModelActivities);
}
