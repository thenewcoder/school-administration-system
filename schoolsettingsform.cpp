﻿#include "schoolsettingsform.h"
#include "ui_schoolsettingsform.h"

#include <QFileDialog>
#include "databasemanager.h"

#include <QDebug>

SchoolSettingsForm::SchoolSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchoolSettingsForm)
{
    ui->setupUi(this);

    setupConnections();
}

SchoolSettingsForm::~SchoolSettingsForm()
{
    delete ui;
}

void SchoolSettingsForm::setupConnections()
{
    // connects to help check if any settings have changed
    connect(ui->leSchoolName, SIGNAL(textEdited(QString)), this, SLOT(onSettingsHaveChanged()));
    connect(ui->teAddress, SIGNAL(textChanged()), this, SLOT(onSettingsHaveChanged()));
    connect(ui->lePhoneNumber, SIGNAL(textEdited(QString)), this, SLOT(onSettingsHaveChanged()));
    connect(ui->leEmail, SIGNAL(textEdited(QString)), this, SLOT(onSettingsHaveChanged()));

    connect(ui->btnAddLogo, &QPushButton::clicked, [this] () {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Choose a picture"),
                                                        "",
                                                        tr("Images (*.png *.bmp *.jpg)"));
        if (!filename.isEmpty())
        {
            QPixmap p(filename);
            QPixmap logo = p.scaled(200, 150, Qt::KeepAspectRatio);
            ui->lblSchoolLogo->setPixmap(logo);

            onSettingsHaveChanged();
        }
    });

    connect(ui->btnRemoveLogo, &QPushButton::clicked, [this] () {
        ui->lblSchoolLogo->setPixmap(QPixmap(":/images/your_logo_here.png"));

        onSettingsHaveChanged();
    });

    connect(ui->btnSaveSettings, &QPushButton::clicked, [this] () {

        const QPixmap* logo = ui->lblSchoolLogo->pixmap();

        mSchool.setSchoolName(ui->leSchoolName->text());
        mSchool.setSchoolAddress(ui->teAddress->toPlainText());
        mSchool.setSchoolPhone(ui->lePhoneNumber->text());
        mSchool.setSchoolEmail(ui->leEmail->text());
        mSchool.setSchoolLogoPixmap(*logo);

        // save data to the database
        DatabaseManager::instance().saveSchoolData(mSchool);

        // update the school logo
        emit notifySchoolLogoUpdate(*logo);

        // for now - notify the school name has changed. TODO:: make a proper check later
        emit notifySchoolNameChanged(ui->leSchoolName->text());

        // toggle the save button
        toggleSaveButton(false);
    });
}

void SchoolSettingsForm::toggleSaveButton(bool state)
{
    ui->btnSaveSettings->setEnabled(state);
}

void SchoolSettingsForm::onSettingsHaveChanged()
{
    bool hasChanged = false;
    if (mSchool.schoolName() != ui->leSchoolName->text())
        hasChanged = true;
    else if (mSchool.schoolAddress() != ui->teAddress->toPlainText())
        hasChanged = true;
    else if (mSchool.schoolPhone() != ui->lePhoneNumber->text())
        hasChanged = true;
    else if (mSchool.schoolEmail() != ui->leEmail->text())
        hasChanged = true;
    else if(mSchool.schoolLogoPixmap().cacheKey() != ui->lblSchoolLogo->pixmap()->cacheKey())
        hasChanged = true;

    toggleSaveButton(hasChanged);
}

void SchoolSettingsForm::loadDatabaseSettings()
{
    mSchool = DatabaseManager::instance().getSchoolInfo();

    ui->leSchoolName->setText(mSchool.schoolName());
    ui->teAddress->setPlainText(mSchool.schoolAddress());
    ui->lePhoneNumber->setText(mSchool.schoolPhone());
    ui->leEmail->setText(mSchool.schoolEmail());

    QPixmap logo = mSchool.schoolLogoPixmap();
    if (!logo.isNull())
    {
        ui->lblSchoolLogo->setPixmap(mSchool.schoolLogoPixmap());
        emit notifySchoolLogoUpdate(mSchool.schoolLogoPixmap());
    }

    // start with save buttons disabled
    toggleSaveButton(false);
}
