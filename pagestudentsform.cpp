#include "pagestudentsform.h"
#include "ui_pagestudentsform.h"

#include <QFileDialog>
#include <QStandardPaths>

PageStudentsForm::PageStudentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageStudentsForm)
{
    ui->setupUi(this);

    setupConnections();
}

PageStudentsForm::~PageStudentsForm()
{
    delete ui;
}

QString PageStudentsForm::name() const
{
    return ui->leName->text();
}

void PageStudentsForm::setName(const QString &name)
{
    ui->leName->setText(name);
}

QDate PageStudentsForm::dateOfBirth() const
{
    return ui->deBirthDate->date();
}

void PageStudentsForm::setDateOfBirth(const QDate &date)
{
    ui->deBirthDate->setDate(date);
}

QString PageStudentsForm::gender() const
{
    return ui->cbGender->currentText();
}

void PageStudentsForm::setGender(const QString &gender)
{
    ui->cbGender->setCurrentText(gender);
}

QString PageStudentsForm::nationality() const
{
    return ui->cbNationality->currentText();
}

void PageStudentsForm::setNationality(const QString &nationality)
{
    ui->cbNationality->setCurrentText(nationality);
}

QString PageStudentsForm::passportNumber() const
{
    return ui->lePassportNumber->text();
}

void PageStudentsForm::setPassportNumber(const QString &number)
{
    ui->lePassportNumber->setText(number);
}

QString PageStudentsForm::idNumber() const
{
    return ui->leIDNumber->text();
}

void PageStudentsForm::setIdNumber(const QString &number)
{
    ui->leIDNumber->setText(number);
}

QString PageStudentsForm::address() const
{
    return ui->teAddress->toPlainText();
}

void PageStudentsForm::setAddress(const QString &address)
{
    ui->teAddress->setPlainText(address);
}

QString PageStudentsForm::studentPhoneNumber() const
{
    return ui->leStudentPhone->text();
}

void PageStudentsForm::setStudentPhoneNumber(const QString &number)
{
    ui->leStudentPhone->setText(number);
}

QString PageStudentsForm::studentEmail() const
{
    return ui->leStudentEmail->text();
}

void PageStudentsForm::setStudentEmail(const QString &email)
{
    ui->leStudentEmail->setText(email);
}

QString PageStudentsForm::fathersPhoneNumber() const
{
    return ui->leFathersPhone->text();
}

void PageStudentsForm::setFathersPhoneNumber(const QString &number)
{
    ui->leFathersPhone->setText(number);
}

QString PageStudentsForm::mothersPhoneNumber() const
{
    return ui->leMothersPhone->text();
}

void PageStudentsForm::setMothersPhoneNumber(const QString &number)
{
    ui->leMothersPhone->setText(number);
}

QString PageStudentsForm::parentEmail() const
{
    return ui->leParentEmail->text();
}

void PageStudentsForm::setParentEmail(const QString &email)
{
    ui->leParentEmail->setText(email);
}

void PageStudentsForm::setupConnections()
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
