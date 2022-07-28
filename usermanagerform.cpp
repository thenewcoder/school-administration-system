#include "usermanagerform.h"
#include "ui_usermanagerform.h"

#include "useritemdelegate.h"
#include "edituserdialog.h"
#include "databasemanager.h"
#include "user.h"
#include "login.h"
#include "passworddialog.h"

#include <QSqlTableModel>
#include <QMessageBox>
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
    ui->tvUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvUsers->setEditTriggers(QTableView::NoEditTriggers);
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
            // insert new user into database
            DatabaseManager::instance().addUser(addUser.getNewUserData());

            mModel->select();
        }
    });

    connect(ui->btnEdit, &QPushButton::clicked, this, [this] () {
        EditUserDialog editUser(this);

        QModelIndex index = ui->tvUsers->currentIndex();
        if (!index.isValid())
            return;

        QString username = mModel->data(mModel->index(index.row(), FIELDS::USERNAME)).toString();
        User user = DatabaseManager::instance().getUser(username);
        editUser.setUserData(user);

        if (editUser.exec() == QDialog::Accepted)
        {
            DatabaseManager::instance().updateUserDataInfo(user);
            mModel->select();
        }
    });

    connect(ui->btnDelete, &QPushButton::clicked, this, [this] () {

        // validate the selected row
        QModelIndex index = ui->tvUsers->currentIndex();

        if (!index.isValid())
            return;

        auto reply = QMessageBox::warning(this, tr("Delete User"), tr("You're about to delete a user! This can't be undone!\n"
                                                         "Are you sure you want to proceed?"),
                             QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
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

            QString userId = mModel->data(mModel->index(index.row(), FIELDS::ID)).toString();

            if (DatabaseManager::instance().removeUser(userId))
                mModel->select();
        }
    });

    connect(ui->btnResetPassword, &QPushButton::clicked, this, [this] () {

        QModelIndex index = ui->tvUsers->currentIndex();
        if (index.isValid())
        {
            QString userId = mModel->data(mModel->index(index.row(), FIELDS::ID)).toString();
            QString randomPassword = Login::instance().generateRandomPasswordPlainText();
            if (DatabaseManager::instance().updateUserPassword(Login::instance().encryptString(randomPassword), userId))
            {
                QMessageBox::information(this, "Password Reset", "The password for has <font>been</> successfully reset!<br>"
                                                                 "The new temporary password is: <strong>" + randomPassword + "</strong><br>"
                                                                 "Make sure you write it down!");
            }
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
