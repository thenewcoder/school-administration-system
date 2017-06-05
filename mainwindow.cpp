#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "adminmenuform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set statusbar and main tool bar invisible for now while logging in
    ui->statusBar->setVisible(false);
    ui->mainToolBar->setVisible(false);

    ui->memberBoxLayout->addWidget(new AdminMenuForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
