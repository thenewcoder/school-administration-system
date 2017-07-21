#include "editteacherdialog.h"
#include "ui_editteacherdialog.h"

#include "databasemanager.h"
#include "teacher.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStringListModel>

EditTeacherDialog::EditTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTeacherDialog)
{
    ui->setupUi(this);

    ui->cbNationality->setModel(new QStringListModel(DatabaseManager::instance().nationalities()));

    setupConnections();
}

EditTeacherDialog::~EditTeacherDialog()
{
    delete ui;
}

void EditTeacherDialog::setTeacher(const Teacher &teacher)
{
    setName(teacher.name());
    setGender(teacher.gender());
    setNationality(teacher.nationality());
    setAddress(teacher.address());
    setPhoneNumber(teacher.phoneNumber());
}

Teacher EditTeacherDialog::getTeacher() const
{
    Teacher teacher;
    teacher.setName(name());
    teacher.setGender(gender());
    teacher.setNationality(nationality());
    teacher.setAddress(address());
    teacher.setPhoneNumber(phoneNumber());

    return teacher;
}

QString EditTeacherDialog::name() const
{
    return ui->leName->text();
}

void EditTeacherDialog::setName(const QString &name)
{
    ui->leName->setText(name);
}

QString EditTeacherDialog::gender() const
{
    return ui->cbGender->currentText();
}

void EditTeacherDialog::setGender(const QString &gender)
{
    ui->cbGender->setCurrentText(gender);
}

QString EditTeacherDialog::nationality() const
{
    return ui->cbNationality->currentText();
}

void EditTeacherDialog::setNationality(const QString &nationality)
{
    ui->cbNationality->setCurrentText(nationality);
}

QString EditTeacherDialog::address() const
{
    return ui->teAddress->toPlainText();
}

void EditTeacherDialog::setAddress(const QString &address)
{
    ui->teAddress->setPlainText(address);
}

QString EditTeacherDialog::phoneNumber() const
{
    return ui->lePhone->text();
}

void EditTeacherDialog::setPhoneNumber(const QString &phoneNumber)
{
    ui->lePhone->setText(phoneNumber);
}

void EditTeacherDialog::setupConnections()
{
    connect(ui->btnAddPhoto, &QPushButton::clicked, [this] () {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Choose an image"),
                                                        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                        tr("Images (*.png *.bmp *.jpg)"));

        if (!filename.isEmpty())
        {
            QImage img(filename);
            QImage photo = img.scaledToHeight(150);
            ui->lblPhoto->setPixmap(QPixmap::fromImage(photo));
        }
    });


}

void EditTeacherDialog::on_buttonBox_accepted()
{
    accept();
}

void EditTeacherDialog::on_buttonBox_rejected()
{
    reject();
}
