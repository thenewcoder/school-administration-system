#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include "databasemanager.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStringListModel>

EditStudentDialog::EditStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog)
{
    ui->setupUi(this);

    ui->cbNationality->setModel(new QStringListModel(DatabaseManager::instance().nationalities()));

    setupConnections();
}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::on_buttonBox_accepted()
{
    accept();
}

void EditStudentDialog::on_buttonBox_rejected()
{
    reject();
}

QString EditStudentDialog::name() const
{
    return ui->leName->text();
}

void EditStudentDialog::setName(const QString &name)
{
    ui->leName->setText(name);
}

QDate EditStudentDialog::dateOfBirth() const
{
    return ui->deBirthDate->date();
}

void EditStudentDialog::setDateOfBirth(const QDate &date)
{
    ui->deBirthDate->setDate(date);
}

QString EditStudentDialog::gender() const
{
    return ui->cbGender->currentText();
}

void EditStudentDialog::setGender(const QString &gender)
{
    ui->cbGender->setCurrentText(gender);
}

QString EditStudentDialog::nationality() const
{
    return ui->cbNationality->currentText();
}

void EditStudentDialog::setNationality(const QString &nationality)
{
    ui->cbNationality->setCurrentText(nationality);
}

QString EditStudentDialog::passportNumber() const
{
    return ui->lePassportNumber->text();
}

void EditStudentDialog::setPassportNumber(const QString &number)
{
    ui->lePassportNumber->setText(number);
}

QString EditStudentDialog::idNumber() const
{
    return ui->leIDNumber->text();
}

void EditStudentDialog::setIdNumber(const QString &number)
{
    ui->leIDNumber->setText(number);
}

QString EditStudentDialog::address() const
{
    return ui->teAddress->toPlainText();
}

void EditStudentDialog::setAddress(const QString &address)
{
    ui->teAddress->setPlainText(address);
}

QString EditStudentDialog::studentPhoneNumber() const
{
    return ui->leStudentPhone->text();
}

void EditStudentDialog::setStudentPhoneNumber(const QString &number)
{
    ui->leStudentPhone->setText(number);
}

QString EditStudentDialog::studentEmail() const
{
    return ui->leStudentEmail->text();
}

void EditStudentDialog::setStudentEmail(const QString &email)
{
    ui->leStudentEmail->setText(email);
}

QString EditStudentDialog::fathersPhoneNumber() const
{
    return ui->leFathersPhone->text();
}

void EditStudentDialog::setFathersPhoneNumber(const QString &number)
{
    ui->leFathersPhone->setText(number);
}

QString EditStudentDialog::mothersPhoneNumber() const
{
    return ui->leMothersPhone->text();
}

void EditStudentDialog::setMothersPhoneNumber(const QString &number)
{
    ui->leMothersPhone->setText(number);
}

QString EditStudentDialog::parentEmail() const
{
    return ui->leParentEmail->text();
}

void EditStudentDialog::setParentEmail(const QString &email)
{
    ui->leParentEmail->setText(email);
}

void EditStudentDialog::setupConnections()
{
    connect(ui->btnAddPhoto, &QPushButton::clicked, [this] () {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Choose an image"),
                                                        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                        tr("Images (*.png *.bmp *.jpg)"));
        if (!filename.isEmpty())
        {
            QImage img(filename);
            QImage photo = img.scaledToWidth(150);
            ui->lblStudentPhoto->setPixmap(QPixmap::fromImage(photo));
        }
    });
}

