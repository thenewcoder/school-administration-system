#include "pagehomeform.h"
#include "ui_pagehomeform.h"

#include "databasemanager.h"
#include "teacher.h"
#include "student.h"

PageHomeForm::PageHomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHomeForm)
{
    ui->setupUi(this);

    // set up the statistics values
    initClasses();
    initStudents();
    initTeachers();
}

PageHomeForm::~PageHomeForm()
{
    delete ui;
}

void PageHomeForm::initClasses()
{
    ui->lblTotalClasses->setText(QString::number(DatabaseManager::instance().numClasses()));
}

void PageHomeForm::initStudents()
{
    ui->lblTotalStudents->setText(QString::number(DatabaseManager::instance().numStudents()));
}

void PageHomeForm::initTeachers()
{
    ui->lblTotalTeachers->setText(QString::number(DatabaseManager::instance().numTeachers()));
}
