#include "editclassdialog.h"
#include "ui_editclassdialog.h"

#include <QStringListModel>
#include "databasemanager.h"
#include "selectordialog.h"

#include <QDebug>

EditClassDialog::EditClassDialog(const QString &title, QWidget *parent, bool isEditMode) :
    QDialog(parent),
    ui(new Ui::EditClassDialog),
    mModelTeachers(new QStringListModel(this)),
    mModelStudents(new QStringListModel(this)),
    mEditMode(isEditMode)
{
    ui->setupUi(this);

    // set the title for the dialog
    setWindowTitle(title);

    // set up the models for the list views
    ui->lvTeachers->setModel(mModelTeachers);
    ui->lvStudents->setModel(mModelStudents);

    // set up the grades combo box
    QStringList grades;
    grades << "" << DatabaseManager::instance().grades();
    ui->cbGrades->setModel(new QStringListModel(grades));
    ui->cbGrades->model()->sort(0);
    ui->cbGrades->setCurrentIndex(0);

    // set up the subjects combo box
    QStringList subs = DatabaseManager::instance().subjects();
    ui->cbSubject->setModel(new QStringListModel(subs));
    ui->cbSubject->model()->sort(0);
    ui->cbSubject->setCurrentIndex(0);

    // set up the classrooms combo box
    QStringList rooms;
    rooms << "" << DatabaseManager::instance().classrooms();
    ui->cbClassroom->setModel(new QStringListModel(rooms));
    ui->cbClassroom->setCurrentIndex(0);

    setupConnections();

    // start with ok button disabled
    toggleOKButton(false);
}

EditClassDialog::~EditClassDialog()
{
    delete ui;
}

QString EditClassDialog::grade() const
{
    return ui->cbGrades->currentText();
}

void EditClassDialog::setGrade(const QString &grade)
{
    ui->cbGrades->setCurrentText(grade);
}

QString EditClassDialog::className() const
{
    return ui->leClassName->text();
}

void EditClassDialog::setClassname(const QString &name)
{
    ui->leClassName->setText(name);
}

QString EditClassDialog::subject() const
{
    return ui->cbSubject->currentText();
}

void EditClassDialog::setSubject(const QString &subject)
{
    ui->cbSubject->setCurrentText(subject);
}

QString EditClassDialog::classroom() const
{
    return ui->cbClassroom->currentText();
}

void EditClassDialog::setClassroom(const QString &room)
{
    ui->cbClassroom->setCurrentText(room);
}

QStringList EditClassDialog::teachers() const
{
    return mModelTeachers->stringList();
}

void EditClassDialog::setTeachers(const QStringList &teachers)
{
    if (teachers.count("") != 1)
    {
        mModelTeachers->setStringList(teachers);
        mModelTeachers->sort(0);
    }
}

QStringList EditClassDialog::students() const
{
    return mModelStudents->stringList();
}

void EditClassDialog::setStudents(const QStringList &students)
{
    if (students.count("") != 1)
    {
        mModelStudents->setStringList(students);
        mModelStudents->sort(0);
    }
}

void EditClassDialog::setClass(const Class &c)
{
    setGrade(c.getGrade());
    setClassname(c.className());
    setSubject(c.subject());
    setClassroom(c.classRoom());
    setTeachers(c.teachers());
    setStudents(c.students());

    // save a copy of the class object
    mClass = c;

    // setup connections for edit mode
    setupDetectEditConnections();
}

Class EditClassDialog::getClass() const
{
    Class c;
    c.setGrade(grade());
    c.setClassname(className());
    c.setSubject(subject());
    c.setClassroom(classroom());
    c.setTeachers(teachers());
    c.setStudents(students());
    return c;
}

void EditClassDialog::onProfileHasChanged()
{
    bool hasChanged = false;

    if (!ui->leClassName->text().isEmpty() && !mEditMode)
        hasChanged = true;
    if (mEditMode)
    {
        if (mClass.className() != className())
            hasChanged = true;
        else if (mClass.getGrade() != grade())
            hasChanged = true;
        else if (mClass.subject() != subject())
            hasChanged = true;
        else if (mClass.classRoom() != classroom())
            hasChanged = true;

        // check if the associated teachers list has changed
        if (mClass.teachers().length() != mModelTeachers->stringList().length())
            hasChanged = true;
        else // same length but values might be different
        {
            QStringList tmp = mClass.teachers();

            for (QString &v : mModelTeachers->stringList())
            {
                if (tmp.contains(v)) // if found in tmp remove it
                    tmp.removeOne(v);
            }

            // if length of tmp is not zero, a change has been made
            if (!tmp.isEmpty())
                hasChanged = true;
        }

        // check if the associated students list has changed
        if (mClass.students().length() != mModelStudents->stringList().length())
            hasChanged = true;
        else // same length but values might be different
        {
            QStringList tmp = mClass.students();

            for (QString &v : mModelStudents->stringList())
            {
                if (tmp.contains(v)) // if found in tmp remove it
                    tmp.removeOne(v);
            }

            // if length of tmp is not zero, a change has been made
            if (!tmp.isEmpty())
                hasChanged = true;
        }
    }
    toggleOKButton(hasChanged);
}

void EditClassDialog::setupConnections()
{
    // add connection to check if the save button should be enabled or disabled
    connect(ui->leClassName, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));

    // edit associated teachers
    connect(ui->btnEditTeachers, &QPushButton::clicked, [this] () {
        QStringList all = DatabaseManager::instance().teachers();
        SelectorDialog edit(tr("Edit Teachers"),
                            all,
                            teachers(), this);

        if (edit.exec() == QDialog::Accepted)
        {
            // set the new teachers string list
            setTeachers(edit.getItems());

            onProfileHasChanged();
        }
    });

    // edit associated students
    connect(ui->btnEditStudents, &QPushButton::clicked, [this] () {
        QStringList all = DatabaseManager::instance().students();
        SelectorDialog edit(tr("Edit Students"),
                            all,
                            students(), this);

        if (edit.exec() == QDialog::Accepted)
        {
            // set the new students string list
            setStudents(edit.getItems());

            onProfileHasChanged();
        }
    });
}

void EditClassDialog::setupDetectEditConnections()
{
    // add connections specifically for edit mode
    connect(ui->cbGrades, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->cbSubject, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->cbClassroom, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
}

void EditClassDialog::toggleOKButton(bool state)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(state);
}

void EditClassDialog::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QDialog::changeEvent(e);
}
