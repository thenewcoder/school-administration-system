#include "adminmenuform.h"
#include "ui_adminmenuform.h"

#include "pagehomeform.h"
#include "pagesettingsform.h"
#include "pageteachersform.h"
#include "pagestudentsform.h"
#include "pageclassesform.h"

AdminMenuForm::AdminMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenuForm)
{
    ui->setupUi(this);

    // make the home button selected by default
    ui->menuListWidget->setCurrentRow(MenuItems::HOME);
    ui->menuPagesStackedWidget->setCurrentIndex(MenuItems::HOME);

    // add the menu items
    ui->loHome->addWidget(new PageHomeForm(this));
    ui->loSettings->addWidget(new PageSettingsForm(this));
    ui->loTeachers->addWidget(new PageTeachersForm(this));
    ui->loStudents->addWidget(new PageStudentsForm(this));
    ui->loClasses->addWidget(new PageClassesForm(this));

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
}
