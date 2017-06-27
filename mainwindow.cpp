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

    ui->memberBoxLayout->addWidget(new AdminMenuForm);

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->loginButton, &QPushButton::clicked, [this] () {
        if (Login::validLogin(ui->usernameEdit->text(), ui->passwordEdit->text()))
        {
            ui->stackedWidget->setCurrentWidget(ui->memberPage);
        }
    });
}
