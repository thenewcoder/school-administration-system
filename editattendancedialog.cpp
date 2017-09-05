#include "editattendancedialog.h"
#include "ui_editattendancedialog.h"

#include <QStringListModel>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QDate>
#include <QLocale>
#include "databasemanager.h"
#include "classrecord.h"

#include <QDebug>
#include <QRadioButton>

EditAttendanceDialog::EditAttendanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAttendanceDialog),
    mModelClasses(new QStringListModel(this)),
    mModelTeachers(new QStringListModel(this)),
    mIsEditMode(false)
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

    // setup the attendance table widget
    ui->twAttendance->setColumnCount(4);
    ui->twAttendance->setSelectionMode(QAbstractItemView::NoSelection);
    ui->twAttendance->setFocusPolicy(Qt::NoFocus);

    // set the attendance possibilities
    QStringList headerLabels;
    headerLabels << tr("Students") << tr("Present") << tr("Absent") << tr("Absent W/ Excuse");

    // set headers
    ui->twAttendance->setHorizontalHeaderLabels(headerLabels);
    ui->twAttendance->setColumnWidth(0, 220);

    ui->twAttendance->sortByColumn(0, Qt::AscendingOrder);

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
    record.setAttendance(getAttendance());
    return record;
}

void EditAttendanceDialog::setClassRecord(const ClassRecord &record)
{
    setRecordId(record.getRecordId());
    setClass(record.getClass());
    setDate(record.getDate());
    setTeacher(record.getTeacher());

    // prepare the table widget
    setAttendance(DatabaseManager::instance().studentsOfClass(getClass()),
                  record.getAttendance());

    // don't let the user edit the class combo box
    ui->cbClasses->setEnabled(false);
}

QString EditAttendanceDialog::getRecordId() const
{
    return mRecordId;
}

void EditAttendanceDialog::setRecordId(const QString &recordId)
{
    mRecordId = recordId;
}

QMap<QString, int> EditAttendanceDialog::getAttendance() const
{
    QMap<QString, int> att;

    // get the number of rows in the table
    int rows = ui->twAttendance->rowCount();

    for (int row = 0; row < rows; ++row)
    {
        // check each radio button if it's checked or not
        for (int col = 1; col <= 3; ++col)
        {
            QRadioButton *btn = ui->twAttendance->cellWidget(row, col)->findChild<QRadioButton*>();
            if (btn->isChecked()) // if attendance has been found
            {
                // get the student name
                QString name = ui->twAttendance->item(row, 0)->text();

                // add the key and value
                att.insert(name, col);
            }
        }
    }
    return att;
}

void EditAttendanceDialog::setAttendance(const QStringList &students, const QMap<QString, int> &attendance)
{
    bool takeAttendance = !attendance.isEmpty(); // not empty

    // populate the table widget
    int row = 0;
    for (auto &student : students)
    {
        // insert a new row
        ui->twAttendance->insertRow(row);

        // add students
        QTableWidgetItem *item = new QTableWidgetItem(student);
        ui->twAttendance->setItem(row, 0, item);

        // add a radio button for the remaining columns
        QButtonGroup *grp = new QButtonGroup;
        for (int col = 1; col <= 3; ++col)
        {
            // create the radio button
            QRadioButton *rbtn = new QRadioButton;
            grp->addButton(rbtn);

            if (takeAttendance) // TODO: clean this up a bit
            {
                if (attendance.contains(student))
                {
                    int val = attendance.value(student);
                    if (val == col)
                        rbtn->setChecked(true);
                }

            }

            // Create an empty widget
            QWidget *wdg = new QWidget;

            // create a layout for the empty widget and add the radio button
            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(rbtn);
            layout->setAlignment(Qt::AlignCenter);
            layout->setSpacing(0); // needed?
            layout->setMargin(0);

            // add layout to the empty widget
            wdg->setLayout(layout);

            // add widget to the cell
            ui->twAttendance->setCellWidget(row, col, wdg);
        }

        // go to the next row
        ++row;
    }
}

void EditAttendanceDialog::setIsEditMode(bool isEditmode)
{
    mIsEditMode = isEditmode;

    // will disable the classes combo box if we're in edit more only
    //ui->cbClasses->setEnabled(!isEditmode);
}

void EditAttendanceDialog::setupConnections()
{
    connect(ui->cbClasses, &QComboBox::currentTextChanged, [this] (const QString &text) {
        if (ui->cbClasses->currentIndex() != 0 && !mIsEditMode)
        {
            // first clear the table widget
            ui->twAttendance->clearContents();
            ui->twAttendance->setRowCount(0);

            // populate the table widget with the students from the selected class only
            setAttendance(DatabaseManager::instance().studentsOfClass(text));
        }
    });
}

bool EditAttendanceDialog::getIsEditMode() const
{
    return mIsEditMode;
}

void EditAttendanceDialog::accept()
{
    // TODO: add ways to notify user visually on screen
    if (ui->cbClasses->currentIndex() != 0 &&
        ui->cbTeachers->currentIndex() != 0)
    {
        if (mIsEditMode) // if we are editing an existing record
        {
            // update the record in the database
            DatabaseManager::instance().saveClassRecord(getClassRecord());
        }
        else // creating a new record
        {
            // insert the new class record to the database
            DatabaseManager::instance().addClassRecord(getClassRecord());
        }
        QDialog::accept();
    }
}
