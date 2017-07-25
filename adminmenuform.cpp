#include "adminmenuform.h"
#include "ui_adminmenuform.h"

#include "pagehomeform.h"
#include "pagesettingsform.h"
#include "pageteachersform.h"
#include "pagestudentsform.h"
#include "pageclassesform.h"

AdminMenuForm::AdminMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenuForm),
    mPageHomeForm(new PageHomeForm(this)),
    mPageStudentsForm(new PageStudentsForm(this)),
    mPageTeachersForm(new PageTeachersForm(this))
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
    ui->loClasses->addWidget(new PageClassesForm(this));

    setupConnections();
}

AdminMenuForm::~AdminMenuForm()
{
    delete ui;
}

void AdminMenuForm::setUsername(const QString &username)
{
    ui->lblWelcomeText->setText("Welcome, " + username);
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

    // page home tab slots with teacher and student slots
    connect(mPageStudentsForm, &PageStudentsForm::notifyStudentChanged, mPageHomeForm, &PageHomeForm::initStudents);
    connect(mPageTeachersForm, &PageTeachersForm::notifyTeacherChanged, mPageHomeForm, &PageHomeForm::initTeachers);
}

void AdminMenuForm::updateSchoolLogo(const QPixmap &logo)
{
    ui->lblSchoolLogo->setPixmap(logo);
}
