#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include "user.h"
#include "databasemanager.h"
#include "login.h"

#include <QRegExpValidator>
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

    ui->leUsername->setFocus();

    // add validator to username lineedit - no spaces allowed
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\-@!#\\$]{3,16}"), this);
    ui->leUsername->setValidator(validator);
    ui->leUsername->setPlaceholderText(tr("3-16 characters"));

    setupConnections();
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::setUserData(User &user)
{
    // change the default behaviour
    connect(ui->btnAddUpdateUser, &QPushButton::clicked, this, &EditUserDialog::updateUserData);

    mUser = &user;
    ui->leUsername->setText(user.username());
    ui->leFullname->setText(user.fullName());
    ui->cbUserType->setCurrentIndex(user.userType() - 1);

    if (user.connectedTeacher() > 0)
    {
        QString connectedTeacherName  = DatabaseManager::instance().getTeacherName(user.connectedTeacher());
        ui->cbConnectedTeacher->setCurrentText(connectedTeacherName);
    }

    // set the accept button text to indicate we are editing/updating
    ui->btnAddUpdateUser->setText(tr("Update User"));
}

User& EditUserDialog::getNewUserData()
{
    mUser = new User;
    mUser->setUsername(ui->leUsername->text());
    mUser->setFullName(ui->leFullname->text());
    mUser->setUserType(ui->cbUserType->currentIndex() + 1);

    if (ui->cbConnectedTeacher->currentIndex() != 0)
    {
        int teacherId  = DatabaseManager::instance().getTeacherId(ui->cbConnectedTeacher->currentText());
        mUser->setConnectedTeacher(teacherId);
    }

    // NOTE: need to set value to indicate that the user needs to update the password later!
    mUser->setPassword(Login::instance().generateRandomPassword());

    return *mUser;
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
    connect(ui->btnAddUpdateUser, &QPushButton::clicked, this, &EditUserDialog::accept); // default behaviour

    connect(ui->leUsername, &QLineEdit::textChanged, this, [this] (const QString &newText) {
        if (mUser != nullptr && mUser->username() != newText)  // TODO: optimize logic
        {
            if (DatabaseManager::instance().isUsernameTaken(newText))
                ui->btnAddUpdateUser->setDisabled(true);
            else
                ui->btnAddUpdateUser->setDisabled(false);
        }
        else if (mUser == nullptr)
        {
            if (DatabaseManager::instance().isUsernameTaken(newText))
                ui->btnAddUpdateUser->setDisabled(true);
            else
                ui->btnAddUpdateUser->setDisabled(false);
        }
        else
            ui->btnAddUpdateUser->setDisabled(false);
    });
}
