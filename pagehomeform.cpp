#include "pagehomeform.h"
#include "ui_pagehomeform.h"

#include "databasemanager.h"
#include "school.h"


PageHomeForm::PageHomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHomeForm)
{
    ui->setupUi(this);

    // set up the statistics values
    initClasses();
    initStudents();
    initTeachers();

    // set the school name as the title if a name exists
    QString title = DatabaseManager::instance().getSchoolInfo().schoolName();

    if (!title.isEmpty())
        ui->lblTitle->setText(title);

}

PageHomeForm::~PageHomeForm()
{
    delete ui;
}

void PageHomeForm::onSchoolNameChanged(const QString &name)
{
    if (!name.isEmpty())
        ui->lblTitle->setText(name);
    else
        ui->lblTitle->setText(tr("Home"));
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

void PageHomeForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QWidget::changeEvent(e);
}
