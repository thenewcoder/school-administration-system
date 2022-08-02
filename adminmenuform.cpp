#include "adminmenuform.h"
#include "ui_adminmenuform.h"

#include "pagehomeform.h"
#include "pagesettingsform.h"
#include "pageteachersform.h"
#include "pagestudentsform.h"
#include "pageattendanceform.h"
#include "pageclassesform.h"
#include "pageotherform.h"
#include "pageactivitiesform.h"
#include "login.h"


AdminMenuForm::AdminMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenuForm),
    mPageHomeForm(new PageHomeForm(this)),
    mPageStudentsForm(new PageStudentsForm(this)),
    mPageTeachersForm(new PageTeachersForm(this)),
    mPageClassesForm(new PageClassesForm(this)),
    mPageAttendanceForm(new PageAttendanceForm(this)),
    mPageOtherForm(new PageOtherForm(this)),
    mPageActivitiesForm(new PageActivitiesForm(this))
{
    ui->setupUi(this);

    // make the home button selected by default
    ui->menuListWidget->setCurrentRow(MenuItems::HOME);
    ui->menuPagesStackedWidget->setCurrentIndex(MenuItems::HOME);

    // add the menu items
    ui->loHome->addWidget(mPageHomeForm);
    ui->loSettings->addWidget(new PageSettingsForm(mPageHomeForm, this));
    ui->loTeachers->addWidget(mPageTeachersForm);
    ui->loStudents->addWidget(mPageStudentsForm);
    ui->loClasses->addWidget(mPageClassesForm);
    ui->loAttendance->addWidget(mPageAttendanceForm);
    ui->loOther->addWidget(mPageOtherForm);
    ui->loActivities->addWidget(mPageActivitiesForm);

    // update the app version label
    ui->lblAppVersion->setText(QString("v.%1").arg(qApp->applicationVersion()));

    setupConnections();
}

AdminMenuForm::~AdminMenuForm()
{
    delete ui;
}

void AdminMenuForm::setupConnections()
{
    // list widget
    connect(ui->menuListWidget, &QListWidget::currentRowChanged, this, [this] (int currentRow) {
        ui->menuPagesStackedWidget->setCurrentIndex(currentRow);
    });

    // user pressing logout button
    connect(ui->btnLogout, &QPushButton::clicked, this, [this] () {
       emit notifyLoggingOut();
    });

    // connect signals and slots from the different pages
    connect(mPageStudentsForm, &PageStudentsForm::notifyStudentChanged, mPageHomeForm, &PageHomeForm::initStudents);
    connect(mPageStudentsForm, &PageStudentsForm::notifyStudentChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageTeachersForm, &PageTeachersForm::notifyTeacherChanged, mPageHomeForm, &PageHomeForm::initTeachers);
    connect(mPageTeachersForm, &PageTeachersForm::notifyTeacherChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageClassesForm, &PageClassesForm::notifyClassesChanged, mPageHomeForm, &PageHomeForm::initClasses);
    connect(mPageClassesForm, &PageClassesForm::notifyClassesChanged, mPageTeachersForm, &PageTeachersForm::updateTeacherTable);
    connect(mPageClassesForm, &PageClassesForm::notifyClassesChanged, mPageAttendanceForm, &PageAttendanceForm::updateAttendanceTable);
    connect(mPageOtherForm, &PageOtherForm::notifySubjectsChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageOtherForm, &PageOtherForm::notifyClassroomsChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageOtherForm, &PageOtherForm::notifyGradesChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageOtherForm, &PageOtherForm::notifyGradesChanged, mPageStudentsForm, &PageStudentsForm::updateStudentsTable);
    connect(mPageOtherForm, &PageOtherForm::notifyDormsChanged, mPageStudentsForm, &PageStudentsForm::updateStudentsTable);
    connect(mPageOtherForm, &PageOtherForm::notifySubjectsChanged, mPageTeachersForm, &PageTeachersForm::updateTeacherTable);

    // pass along the signal - NOTE: any better way?
    connect(mPageTeachersForm, &PageTeachersForm::notifyTeacherChanged, this,  &AdminMenuForm::notifyTeachersUpdated);
}

void AdminMenuForm::setWelcomeMessage(const QString &name)
{
    ui->lblWelcomeText->setText(tr("Welcome, %1").arg(name));
}

void AdminMenuForm::updateSchoolLogo(const QPixmap &logo)
{
    ui->lblMenuSchoolLogo->setPixmap(logo);
}

void AdminMenuForm::handleUserLogin()
{
    // setup the username
    QString name = !Login::instance().fullname().isEmpty() ? Login::instance().fullname() : Login::instance().username();
    setWelcomeMessage(name);

    emit notifyUserLogon();
}

void AdminMenuForm::onFullnameChanged(const QString &name)
{
    setWelcomeMessage(name);
}

void AdminMenuForm::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        // setup the username
        QString name = !Login::instance().fullname().isEmpty() ? Login::instance().fullname() : Login::instance().username();
        setWelcomeMessage(name);
    }
    QWidget::changeEvent(e);
}
