#include "usermanagerform.h"
#include "ui_usermanagerform.h"

#include "useritemdelegate.h"

#include <QSqlTableModel>

UserManagerForm::UserManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagerForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("user");
    mModel->select();
    mModel->sort(FIELDS::ID, Qt::AscendingOrder);

    addTableHeaders();

    ui->tvUsers->setModel(mModel);
    ui->tvUsers->setItemDelegateForColumn(FIELDS::USERTYPE, new UserItemDelegate);
    ui->tvUsers->hideColumn(FIELDS::PASSWORD);
    ui->tvUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvUsers->resizeRowsToContents();
}

UserManagerForm::~UserManagerForm()
{
    delete ui;
}

void UserManagerForm::addTableHeaders()
{
    mModel->setHeaderData(FIELDS::ID, Qt::Horizontal, tr("ID"));
    mModel->setHeaderData(FIELDS::USERNAME, Qt::Horizontal, tr("Username"));
    mModel->setHeaderData(FIELDS::FULLNAME, Qt::Horizontal, tr("Full Name"));
    mModel->setHeaderData(FIELDS::USERTYPE, Qt::Horizontal, tr("User Type"));
}

void UserManagerForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        addTableHeaders();
    }
    QWidget::changeEvent(e);
}
