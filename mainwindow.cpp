#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "adminmenuform.h"
#include "login.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    adminMenuForm(new AdminMenuForm(this))
{
    ui->setupUi(this);

    // set statusbar and main tool bar invisible for now while logging in
    ui->statusBar->setVisible(false);
    ui->mainToolBar->setVisible(false);

    ui->memberBoxLayout->addWidget(adminMenuForm);

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
        if (Login::validLogin(username(), password()))
        {
            adminMenuForm->setUser(Login::getUserData(username()));
            ui->stackedWidget->setCurrentWidget(ui->memberPage);
        }
    });

    // log out user
    connect(adminMenuForm, &AdminMenuForm::notifyLoggingOut, [this] () {
        ui->stackedWidget->setCurrentWidget(ui->loginPage);

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
