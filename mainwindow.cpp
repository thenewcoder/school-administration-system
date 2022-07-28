#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "adminmenuform.h"
#include "teachermenuform.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    adminMenuForm(nullptr),
    teacherMenuForm(nullptr)
{
    ui->setupUi(this);

    // set the application icon
    setWindowIcon(QIcon(":/images/app.ico"));

    // set statusbar and main tool bar invisible for now while logging in
    ui->statusBar->setVisible(false);
    ui->mainToolBar->setVisible(false);

    // make the invalid username/password label invisible at startup
    ui->lblInvalidUserPass->setVisible(false);

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // log in user
    connect(ui->loginButton, &QPushButton::clicked, this, [this] () {
        if (Login::instance().validLogin(username(), password()))
        {
            int usertype = Login::instance().getUserType();
            if (usertype == Login::UserType::Admin)
                setupNewAdminForm();
            else if (usertype == Login::UserType::Teacher)
                setupNewTeacherForm();

            emit notifyUserLogin();
        }
        else
        {
            // make the label visible when the user got the wrong password
            ui->lblInvalidUserPass->setVisible(true);
        }
    });

    // add connection so that the user can press return after entering the password
    connect(ui->passwordEdit, &QLineEdit::returnPressed, ui->loginButton, &QPushButton::click);
}

void MainWindow::setupNewAdminForm()
{
    // create a new admin form
    adminMenuForm = new AdminMenuForm(this);

    // add admin form widget to the stackedwidget
    ui->memberBoxLayout->addWidget(adminMenuForm);

    // show logged in pages
    ui->stackedWidget->setCurrentWidget(ui->memberPage);

    // set up the connections
    connect(this, &MainWindow::notifyUserLogin, adminMenuForm, &AdminMenuForm::handleUserLogin);

    // log out user
    connect(adminMenuForm, &AdminMenuForm::notifyLoggingOut, this, [this] () {
        ui->stackedWidget->setCurrentWidget(ui->loginPage);

        // delete the adminMenuForm on logout
        delete adminMenuForm;
        adminMenuForm = nullptr;

        // delete the previous login information
        ui->passwordEdit->setText("");
        ui->usernameEdit->setText("");
        ui->usernameEdit->setFocus();

        // make the label invisible just in case
        ui->lblInvalidUserPass->setVisible(false);
    });
}

void MainWindow::setupNewTeacherForm()
{
    // create a new teacher form
    teacherMenuForm = new TeacherMenuForm(this);

    // add admin form widget to the stackedwidget
    ui->memberBoxLayout->addWidget(teacherMenuForm);

    // show logged in pages
    ui->stackedWidget->setCurrentWidget(ui->memberPage);

    // set up the connections
    connect(this, &MainWindow::notifyUserLogin, teacherMenuForm, &TeacherMenuForm::handleUserLogin);

    // log out user
    connect(teacherMenuForm, &TeacherMenuForm::notifyLoggingOut, this, [this] () {
        ui->stackedWidget->setCurrentWidget(ui->loginPage);

        // delete the adminMenuForm on logout
        delete teacherMenuForm;
        teacherMenuForm = nullptr;

        // delete the previous login information
        ui->passwordEdit->setText("");
        ui->usernameEdit->setText("");
        ui->usernameEdit->setFocus();

        // make the label invisible just in case
        ui->lblInvalidUserPass->setVisible(false);
    });
}

QString MainWindow::username() const
{
    return ui->usernameEdit->text();
}

QString MainWindow::password() const
{
    return ui->passwordEdit->text();
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    QMainWindow::changeEvent(e);
}
