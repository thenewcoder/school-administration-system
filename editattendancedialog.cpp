#include "editattendancedialog.h"
#include "ui_editattendancedialog.h"

#include <QStringListModel>
#include <QSqlTableModel>
#include <QDate>
#include <QLocale>
#include "databasemanager.h"
#include "classrecord.h"

#include <QDebug>

EditAttendanceDialog::EditAttendanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAttendanceDialog),
    mModelClasses(new QStringListModel(this)),
    mModelTeachers(new QStringListModel(this)),
    mModelAttendance(new QSqlTableModel(this))
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

    // set up the attendance table view
    mModelAttendance->setTable("attendance_summary");
    mModelAttendance->setHeaderData(FIELDS::STUDENT, Qt::Horizontal, tr("Student"));
    mModelAttendance->setHeaderData(FIELDS::STATUS, Qt::Horizontal, tr("Status"));
    ui->tvAttendance->setModel(mModelAttendance);

    // hide the class name column
    ui->tvAttendance->hideColumn(FIELDS::CLASS);


    setupConnections();
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
    QDate d = ui->deClassTime->date();
    return QLocale("en_US").toString(d, "yyyy-MM-dd");
}

void EditAttendanceDialog::setDate(const QString &date)
{
    QDate d = QLocale("en_US").toDate(date, "yyyy-MM-dd");
    ui->deClassTime->setDate(d);
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
    record.setRecordId(getRecordId());
    record.setClass(getClass());
    record.setDate(getDate());
    record.setTeacher(getTeacher());
    return record;
}

void EditAttendanceDialog::setClassRecord(const ClassRecord &record)
{
    setRecordId(record.getRecordId());
    setClass(record.getClass());
    setDate(record.getDate());
    setTeacher(record.getTeacher());
}

QString EditAttendanceDialog::getRecordId() const
{
    return mRecordId;
}

void EditAttendanceDialog::setRecordId(const QString &recordId)
{
    mRecordId = recordId;
}

void EditAttendanceDialog::setupConnections()
{
    connect(ui->cbClasses, &QComboBox::currentTextChanged, [this] (const QString &text) {
        if (ui->cbClasses->currentIndex() != 0)
        {
            mModelAttendance->setFilter(QString("Class = '%1'").arg(text));
            mModelAttendance->select();
        }
    });
}
