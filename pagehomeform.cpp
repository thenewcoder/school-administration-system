#include "pagehomeform.h"
#include "ui_pagehomeform.h"

#include "databasemanager.h"

PageHomeForm::PageHomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHomeForm)
{
    ui->setupUi(this);

    // set up the statistics values
    ui->lblTotalClasses->setText(QString::number(DatabaseManager::instance().numClasses()));
    ui->lblTotalTeachers->setText(QString::number(DatabaseManager::instance().numTeachers()));
    ui->lblTotalStudents->setText(QString::number(DatabaseManager::instance().numStudents()));
}

PageHomeForm::~PageHomeForm()
{
    delete ui;
}
