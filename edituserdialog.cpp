#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include "user.h"
#include "databasemanager.h"

#include <QDebug>

EditUserDialog::EditUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);

    // setup usertype combo box
    ui->cbUserType->addItems(QStringList{tr("Administrator"), tr("Teacher")});

    // setup connect user combo box
    QStringList users{tr("No")};
    users << DatabaseManager::instance().users();
    ui->cbConnectUser->addItems(users);

    setupConnections();
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::setUser(const User &user)
{
    ui->leUsername->setText(user.username());
    ui->leFullname->setText(user.fullName());
    ui->cbUserType->setCurrentIndex(user.userType() - 1);
    ui->cbConnectUser->setCurrentIndex(user.connectedUser()); // TODO: adapt code to look for the correct user
}

void EditUserDialog::setupConnections()
{
    connect(ui->btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnAddUpdateUser, &QPushButton::clicked, this, &QDialog::accept);
}
