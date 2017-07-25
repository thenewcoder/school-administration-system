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
            emit notifySchoolLogoUpdate(logo);
        }
    });

    connect(ui->btnRemoveLogo, &QPushButton::clicked, [this] () {
        QPixmap p(":/images/your_logo_here.png");
        ui->lblSchoolLogo->setPixmap(p);
        emit notifySchoolLogoUpdate(p);
    });
}
