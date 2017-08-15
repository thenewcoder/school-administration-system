#include "adminmenuform.h"
#include "ui_adminmenuform.h"

#include "pagehomeform.h"
#include "pagesettingsform.h"
#include "pageteachersform.h"
#include "pagestudentsform.h"
#include "pageclassesform.h"
#include "pageotherform.h"
#include "login.h"

AdminMenuForm::AdminMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenuForm),
    mPageHomeForm(new PageHomeForm(this)),
    mPageStudentsForm(new PageStudentsForm(this)),
    mPageTeachersForm(new PageTeachersForm(this)),
    mPageClassesForm(new PageClassesForm(this)),
    mPageOtherForm(new PageOtherForm(this))
{
    ui->setupUi(this);

    // make the home button selected by default
    ui->menuListWidget->setCurrentRow(MenuItems::HOME);
    ui->menuPagesStackedWidget->setCurrentIndex(MenuItems::HOME);

    // add the menu items
    ui->loHome->addWidget(mPageHomeForm);
    ui->loSettings->addWidget(new PageSettingsForm(this));
    ui->loTeachers->addWidget(mPageTeachersForm);
    ui->loStudents->addWidget(mPageStudentsForm);
    ui->loClasses->addWidget(mPageClassesForm);
    ui->loOther->addWidget(mPageOtherForm);

    setupConnections();
}

AdminMenuForm::~AdminMenuForm()
{
    delete ui;
}

void AdminMenuForm::setupConnections()
{
    // list widget
    connect(ui->menuListWidget, &QListWidget::currentRowChanged, [this] (int currentRow) {
        ui->menuPagesStackedWidget->setCurrentIndex(currentRow);
    });

    // user pressing logout button
    connect(ui->btnLogout, &QPushButton::clicked, [this] () {
       emit notifyLoggingOut();
    });

    // connect signals and slots from the different pages
    connect(mPageStudentsForm, &PageStudentsForm::notifyStudentChanged, mPageHomeForm, &PageHomeForm::initStudents);
    connect(mPageStudentsForm, &PageStudentsForm::notifyStudentChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageTeachersForm, &PageTeachersForm::notifyTeacherChanged, mPageHomeForm, &PageHomeForm::initTeachers);
    connect(mPageTeachersForm, &PageTeachersForm::notifyTeacherChanged, mPageClassesForm, &PageClassesForm::updateClassTable);
    connect(mPageClassesForm, &PageClassesForm::notifyClassesChanged, mPageHomeForm, &PageHomeForm::initClasses);
    connect(mPageClassesForm, &PageClassesForm::notifyClassesChanged, mPageTeachersForm, &PageTeachersForm::updateTeacherTable);
}

void AdminMenuForm::updateSchoolLogo(const QPixmap &logo)
{
    ui->lblSchoolLogo->setPixmap(logo);
}

void AdminMenuForm::handleUserLogin()
{
    QString name = !Login::instance().fullname().isEmpty() ? Login::instance().fullname() : Login::instance().username();
    ui->lblWelcomeText->setText(tr("Welcome, ") + name);
    emit notifyUserLogon();
}
