#include "editattendancedialog.h"
#include "ui_editattendancedialog.h"

#include <QStringListModel>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QDate>
#include <QLocale>
#include "databasemanager.h"

#include <QDebug>
#include <QPushButton>
#include <QRadioButton>

EditAttendanceDialog::EditAttendanceDialog(QWidget *parent, bool isEditMode) :
    QDialog(parent),
    ui(new Ui::EditAttendanceDialog),
    mModelClasses(new QStringListModel(this)),
    mModelTeachers(new QStringListModel(this)),
    mEditMode(isEditMode)
{
    ui->setupUi(this);

    // set up the classes combo box
    ui->cbClasses->setModel(mModelClasses);
    QStringList classes;
    classes << tr("Select one") << DatabaseManager::instance().classes();
    mModelClasses->setStringList(classes);
    ui->cbClasses->setCurrentIndex(0);

    // set up the model for the teachers combo box
    ui->cbTeachers->setModel(mModelTeachers);

    // set the date edit to todays date
    ui->deClassTime->setDate(QDate::currentDate());

    // set the attendance possibilities
    QStringList headerLabels;
    headerLabels << tr("Students") << tr("Present") << tr("Absent") << tr("Tardy") <<
                    tr("Absent W/ Excuse") << tr("Tardy W/ Excuse");

    // setup the attendance table widget
    ui->twAttendance->setColumnCount(headerLabels.length());
    ui->twAttendance->setSelectionMode(QAbstractItemView::NoSelection);
    ui->twAttendance->setFocusPolicy(Qt::NoFocus);

    // set headers
    ui->twAttendance->setHorizontalHeaderLabels(headerLabels);
    ui->twAttendance->setColumnWidth(0, 220);

    setupConnections();

    // start with OK button disabled
    toggleOKButton(false);

    // set state of check box depending on the mode
    ui->cbShowAllTeachers->setEnabled(isEditMode);
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
    if (mEditMode)
        return ui->cbTeachers->currentText();
    else if (ui->cbTeachers->currentIndex() != 0)
        return ui->cbTeachers->currentText();
    return QString();
}

void EditAttendanceDialog::setTeacher(const QString &teacher)
{
    if (!teacher.isEmpty())
    {
        if (!mModelTeachers->stringList().contains(teacher))
        {
            QStringList teachers = mModelTeachers->stringList() << teacher;
            mModelTeachers->setStringList(teachers);
        }
        ui->cbTeachers->setCurrentText(teacher);
    }
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

    // for now, just store a copy of the classrecord
    mRecord = record;

    // prepare the table widget
    setAttendance(DatabaseManager::instance().studentsOfClass(getClass()),
                  record.getAttendance());

    // set the correct index to the teachers combo box
    setTeacher(record.getTeacher());

    // don't let the user edit the class combo box
    ui->cbClasses->setEnabled(false);

    // setup edit mode connections
    setupDetectEditConnections();
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
    int columns = ui->twAttendance->columnCount();

    for (int row = 0; row < rows; ++row)
    {
        // check each radio button if it's checked or not
        for (int col = 1; col < columns; ++col)
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
        int num_columns = ui->twAttendance->columnCount();
        for (int col = 1; col < num_columns; ++col)
        {
            // create the radio button
            QRadioButton *rbtn = new QRadioButton;
            grp->addButton(rbtn);

            // setup connections for the radio buttons
            connect(rbtn, SIGNAL(toggled(bool)), this, SLOT(onProfileHasChanged()));

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

void EditAttendanceDialog::populateTeachersBox(const QString &className)
{
    if (mEditMode)
    {
        mModelTeachers->setStringList(DatabaseManager::instance().teachersOfClass(className));
        ui->cbTeachers->setCurrentText(mRecord.getTeacher());
    }
    else
    {
        QStringList teachers;
        teachers << tr("Select one") << DatabaseManager::instance().teachersOfClass(className);
        mModelTeachers->setStringList(teachers);
        ui->cbTeachers->setCurrentIndex(0);
    }
}

void EditAttendanceDialog::setupConnections()
{
    // setup connections to check if enough data has been entered to enable the OK button
    connect(ui->cbClasses, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->cbTeachers, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));

    // classes combo box has changed
    connect(ui->cbClasses, &QComboBox::currentTextChanged, [this] (const QString &text) {
        if (!mEditMode)
        {
            if (ui->cbClasses->currentIndex() != 0) // class is selected
            {
                // first clear the table widget
                ui->twAttendance->clearContents();
                ui->twAttendance->setRowCount(0);

                // populate the table widget with the students from the selected class only
                setAttendance(DatabaseManager::instance().studentsOfClass(text));

                // enable the check box
                ui->cbShowAllTeachers->setEnabled(true);

                // populate the teachers box
                populateTeachersBox(text);
            }
            else if (ui->cbClasses->currentIndex() == 0) // no class is selected
            {
                ui->cbShowAllTeachers->setEnabled(false);
                ui->cbTeachers->clear();
            }
        }
        else // edit mode
        {
            // populate the teachers box
            populateTeachersBox(text);
        }
    });

    // show all teachers check box has changed state
    connect(ui->cbShowAllTeachers, &QCheckBox::toggled, [this] (bool checked) {
        if (checked)
        {
            QString name;
            // first check what the current index is pointing to
            if ((!mEditMode && ui->cbTeachers->currentIndex() != 0) || mEditMode)
            {
                name = ui->cbTeachers->currentText();
            }

            // get all teachers and reset the current text
            QStringList teachers = DatabaseManager::instance().teachers();
            mModelTeachers->setStringList(teachers);

            if (!name.isEmpty())
                setTeacher(name);
            else
                ui->cbTeachers->setCurrentIndex(0);
        }
        else  // checkbox toggled off
        {
            QString name;
            if (!mEditMode)
            {
                name = ui->cbTeachers->currentText();
            }
            else if (mEditMode)
            {
                if (ui->cbTeachers->currentText() != mRecord.getTeacher())
                    name = ui->cbTeachers->currentText();
            }

            populateTeachersBox(getClass());

            // set the correct index to the teachers combo box
            if (mModelTeachers->stringList().contains(name))
                setTeacher(name);
            else if (mEditMode)
                setTeacher(mRecord.getTeacher());
            else
                ui->cbTeachers->setCurrentIndex(0);
        }
    });
}

void EditAttendanceDialog::setupDetectEditConnections()
{
    // additional connections for edit mode
    connect(ui->deClassTime, SIGNAL(dateChanged(QDate)), this, SLOT(onProfileHasChanged()));
}

void EditAttendanceDialog::toggleOKButton(bool state)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(state);
}

void EditAttendanceDialog::onProfileHasChanged()
{
    bool hasChanged = false;

    if (!mEditMode)
    {
        if (ui->cbClasses->currentIndex() != 0 && ui->cbTeachers->currentIndex() != 0)
            hasChanged = true;
    }
    else if (mEditMode)
    {
        // don't need to compare class names because the combo box is disabled by default
        if (mRecord.getDate() != getDate())
            hasChanged = true;
        else if (mRecord.getTeacher() != getTeacher())
            hasChanged = true;
        else if (mRecord.getAttendance() != getAttendance())
            hasChanged = true;
    }
    toggleOKButton(hasChanged);
}
