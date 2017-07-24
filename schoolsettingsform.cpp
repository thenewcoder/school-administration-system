#include "schoolsettingsform.h"
#include "ui_schoolsettingsform.h"

#include <QFileDialog>

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
    connect(ui->btnAddPhoto, &QPushButton::clicked, [this] () {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Choose a picture"),
                                                        "",
                                                        tr("Images (*.png *.bmp *.jpg)"));
        if (!filename.isEmpty())
        {
            QPixmap p(filename);
            QPixmap photo = p.scaledToWidth(200);
            ui->lblSchoolLogo->setPixmap(photo);
        }
    });

    connect(ui->btnRemovePhoto, &QPushButton::clicked, [this] () {
        ui->lblSchoolLogo->setPixmap(QPixmap(":/images/your_logo_here.png"));
    });
}
