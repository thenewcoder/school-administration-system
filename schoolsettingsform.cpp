#include "schoolsettingsform.h"
#include "ui_schoolsettingsform.h"

#include <QFileDialog>

#include "school.h"
#include "databasemanager.h"

SchoolSettingsForm::SchoolSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchoolSettingsForm)
{
    ui->setupUi(this);

    loadDatabaseSettings();

    setupConnections();
}

SchoolSettingsForm::~SchoolSettingsForm()
{
    delete ui;
}

void SchoolSettingsForm::setupConnections()
{
    connect(ui->btnAddLogo, &QPushButton::clicked, [this] () {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Choose a picture"),
                                                        "",
                                                        tr("Images (*.png *.bmp *.jpg)"));
        if (!filename.isEmpty())
        {
            QPixmap p(filename);
            QPixmap logo = p.scaledToWidth(200);
            ui->lblSchoolLogo->setPixmap(logo);
        }
    });

    connect(ui->btnRemoveLogo, &QPushButton::clicked, [this] () {
        ui->lblSchoolLogo->setPixmap(QPixmap(":/images/your_logo_here.png"));
    });

    connect(ui->btnSaveSettings, &QPushButton::clicked, [this] () {

        const QPixmap* logo = ui->lblSchoolLogo->pixmap();

        School school;
        school.setSchoolName(ui->leSchoolName->text());
        school.setSchoolAddress(ui->teAddress->toPlainText());
        school.setSchoolPhone(ui->lePhoneNumber->text());
        school.setSchoolEmail(ui->leEmail->text());
        school.setSchoolLogoPixmap(*logo);

        // save data to the database
        DatabaseManager::instance().saveSchoolData(school);

        // update the school logo

        emit notifySchoolLogoUpdate(*logo);
    });
}

void SchoolSettingsForm::loadDatabaseSettings()
{
    School school = DatabaseManager::instance().getSchoolInfo();

    ui->leSchoolName->setText(school.schoolName());
    ui->teAddress->setPlainText(school.schoolAddress());
    ui->lePhoneNumber->setText(school.schoolPhone());
    ui->leEmail->setText(school.schoolEmail());
    ui->lblSchoolLogo->setPixmap(school.schoolLogoPixmap());

    emit notifySchoolLogoUpdate(school.schoolLogoPixmap());
}
