#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setCentralWidget(ui->stackedWidget); // do I need?

    // set statusbar and main tool bar invisible for now while logging in
    ui->statusBar->setVisible(false);
    ui->mainToolBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
