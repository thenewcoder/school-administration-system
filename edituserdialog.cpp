#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include "user.h"
#include "databasemanager.h"

#include <QDebug>

EditUserDialog::EditUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog),
    mUser(nullptr)
{
    ui->setupUi(this);

    // setup usertype combo box
    ui->cbUserType->addItems(QStringList{tr("Administrator"), tr("Teacher")});

    // setup connect user combo box
    QStringList teachers{tr("No")};
    teachers << DatabaseManager::instance().teachers();
    ui->cbConnectedTeacher->addItems(teachers);

    setupConnections();
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::setUserData(User &user)
{
    mUser = &user;
    ui->leUsername->setText(user.username());
    ui->leFullname->setText(user.fullName());
    ui->cbUserType->setCurrentIndex(user.userType() - 1);

    if (user.connectedTeacher() > 0)
    {
        QString connectedTeacherName  = DatabaseManager::instance().getTeacherName(user.connectedTeacher());
        ui->cbConnectedTeacher->setCurrentText(connectedTeacherName);
    }
}

void EditUserDialog::updateUserData()
{
    mUser->setUsername(ui->leUsername->text());
    mUser->setFullName(ui->leFullname->text());
    mUser->setUserType(ui->cbUserType->currentIndex() + 1);

    if (ui->cbConnectedTeacher->currentIndex() != 0)
    {
        int teacherId  = DatabaseManager::instance().getTeacherId(ui->cbConnectedTeacher->currentText());
        mUser->setConnectedTeacher(teacherId);
    }

    accept();
}

void EditUserDialog::setupConnections()
{
    connect(ui->btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnAddUpdateUser, &QPushButton::clicked, this, &EditUserDialog::updateUserData);

    connect(ui->leUsername, &QLineEdit::textChanged, this, [this] (const QString &change) {
        if (mUser->username() != change)
        {
            if (DatabaseManager::instance().isUsernameTaken(change))
                ui->btnAddUpdateUser->setDisabled(true);
            else
                ui->btnAddUpdateUser->setDisabled(false);
        }
        else
            ui->btnAddUpdateUser->setDisabled(false);
    });
}
