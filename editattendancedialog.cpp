#include "editattendancedialog.h"
#include "ui_editattendancedialog.h"

#include <QStringListModel>
#include <QDate>
#include <QLocale>
#include "databasemanager.h"
#include "classrecord.h"

EditAttendanceDialog::EditAttendanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAttendanceDialog),
    mModelClasses(new QStringListModel(this)),
    mModelTeachers(new QStringListModel(this))
{
    ui->setupUi(this);

    // set up the classes combo box
    ui->cbClasses->setModel(mModelClasses);
    QStringList classes;
    classes << tr("Select one") << DatabaseManager::instance().classes();
    mModelClasses->setStringList(classes);
    ui->cbClasses->setCurrentIndex(0);

    // set up the teachers combo box
    ui->cbTeachers->setModel(mModelTeachers);
    QStringList teachers;
    teachers << tr("Select one") << DatabaseManager::instance().teachers();
    mModelTeachers->setStringList(teachers);
    ui->cbTeachers->setCurrentIndex(0);

    // set the date edit to todays date
    ui->deClassTime->setDate(QDate::currentDate());
}

EditAttendanceDialog::~EditAttendanceDialog()
{
    delete ui;
}

QString EditAttendanceDialog::getClass() const
{
    if (ui->cbClasses->currentIndex() != 0)
    {
        return ui->cbClasses->currentText();
    }
    return QString();
}

void EditAttendanceDialog::setClass(const QString &theClass)
{
    if (!theClass.isEmpty())
    {
        ui->cbClasses->setCurrentText(theClass);
    }
    else
    {
        ui->cbClasses->setCurrentIndex(0);
    }
}

QString EditAttendanceDialog::getDate() const
{
    // TODO: make sure returned date is in correct format
    return ui->deClassTime->date().toString();
}

void EditAttendanceDialog::setDate(const QString &date)
{
    // FIXME: not working properly
    ui->deClassTime->setDate(QDate::fromString(date));
}

QString EditAttendanceDialog::getTeacher() const
{
    if (ui->cbTeachers->currentIndex() != 0)
        return ui->cbTeachers->currentText();
    return QString();
}

void EditAttendanceDialog::setTeacher(const QString &teacher)
{
    if (!teacher.isEmpty())
        ui->cbTeachers->setCurrentText(teacher);
    else
        ui->cbTeachers->setCurrentIndex(0);
}

ClassRecord EditAttendanceDialog::getClassRecord() const
{
    ClassRecord record;
    record.setClass(getClass());
    record.setDate(getDate());
    record.setTeacher(getTeacher());
    return record;
}

void EditAttendanceDialog::setClassRecord(const ClassRecord &record)
{
    setClass(record.getClass());
    setDate(record.getDate());
    setTeacher(record.getTeacher());
}
