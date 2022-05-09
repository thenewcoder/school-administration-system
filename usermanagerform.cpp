#include "usermanagerform.h"
#include "ui_usermanagerform.h"

#include "useritemdelegate.h"
#include "edituserdialog.h"
#include "databasemanager.h"
#include "user.h"

#include <QSqlTableModel>
#include <QDebug>

UserManagerForm::UserManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagerForm),
    mModel(new QSqlTableModel(this))
{
    ui->setupUi(this);

    mModel->setTable("edituser_summary");
    mModel->select();
    mModel->sort(FIELDS::ID, Qt::AscendingOrder);

    addTableHeaders();

    ui->tvUsers->setModel(mModel);
    ui->tvUsers->setItemDelegateForColumn(FIELDS::USERTYPE, new UserItemDelegate);
    //ui->tvUsers->hideColumn(FIELDS::PASSWORD);
    ui->tvUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvUsers->resizeRowsToContents();

    setupConnections();
}

UserManagerForm::~UserManagerForm()
{
    delete ui;
}

void UserManagerForm::addTableHeaders()
{
    mModel->setHeaderData(FIELDS::ID, Qt::Horizontal, tr("Id"));
    mModel->setHeaderData(FIELDS::USERNAME, Qt::Horizontal, tr("Username"));
    mModel->setHeaderData(FIELDS::FULLNAME, Qt::Horizontal, tr("Full Name"));
    mModel->setHeaderData(FIELDS::USERTYPE, Qt::Horizontal, tr("User Type"));
    mModel->setHeaderData(FIELDS::CONNECTED, Qt::Horizontal, tr("Connected"));
}

void UserManagerForm::setupConnections()
{
    connect(ui->btnAdd, &QPushButton::clicked, this, [this] () {
        EditUserDialog addUser(this);

        if (addUser.exec() == QDialog::Accepted)
        {
            qDebug() << "working";
        }
    });

    connect(ui->btnEdit, &QPushButton::clicked, this, [this] () {
        EditUserDialog editUser(this);

        QModelIndex index = ui->tvUsers->currentIndex();
        if (!index.isValid())
            return;

        QString user = mModel->data(mModel->index(index.row(), FIELDS::USERNAME)).toString();
        editUser.setUser(DatabaseManager::instance().getUser(user));

        if (editUser.exec() == QDialog::Accepted)
        {

        }
    });
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
