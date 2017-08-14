#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "adminmenuform.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set statusbar and main tool bar invisible for now while logging in
    ui->statusBar->setVisible(false);
    ui->mainToolBar->setVisible(false);

    setupNewAdminForm();

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // log in user
    connect(ui->loginButton, &QPushButton::clicked, [this] () {
        if (Login::instance().validLogin(username(), password()))
        {
            ui->stackedWidget->setCurrentWidget(ui->memberPage);
            emit notifyUserLogin();
        }
    });
}

void MainWindow::setupNewAdminForm()
{
    // create a new admin form
    adminMenuForm = new AdminMenuForm(this);

    // add admin form widget to the stackedwidget
    ui->memberBoxLayout->addWidget(adminMenuForm);

    // set up the connections
    connect(this, &MainWindow::notifyUserLogin, adminMenuForm, &AdminMenuForm::handleUserLogin);

    // log out user
    connect(adminMenuForm, &AdminMenuForm::notifyLoggingOut, [this] () {
        ui->stackedWidget->setCurrentWidget(ui->loginPage);

        // delete the adminMenuForm on logout and set up a new one - for now
        delete adminMenuForm;
        setupNewAdminForm();

        // delete the previous login information
        ui->passwordEdit->setText("");
        ui->usernameEdit->setText("");
        ui->usernameEdit->setFocus();
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
