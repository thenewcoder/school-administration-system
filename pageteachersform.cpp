#include "pageteachersform.h"
#include "ui_pageteachersform.h"

#include <QFileDialog>
#include <QStandardPaths>

PageTeachersForm::PageTeachersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageTeachersForm)
{
    ui->setupUi(this);

    setupConnections();
}

PageTeachersForm::~PageTeachersForm()
{
    delete ui;
}

QString PageTeachersForm::name() const
{
    return ui->leName->text();
}

void PageTeachersForm::setName(const QString &name)
{
    ui->leName->setText(name);
}

QString PageTeachersForm::gender() const
{
    return ui->cbGender->currentText();
}

void PageTeachersForm::setGender(const QString &gender)
{
    ui->cbGender->setCurrentText(gender);
}

QString PageTeachersForm::nationality() const
{
    return ui->cbNationality->currentText();
}

void PageTeachersForm::setNationality(const QString &nationality)
{
    ui->cbNationality->setCurrentText(nationality);
}

QString PageTeachersForm::address() const
{
    return ui->teAddress->toPlainText();
}

void PageTeachersForm::setAddress(const QString &address)
{
    ui->teAddress->setPlainText(address);
}

QString PageTeachersForm::phoneNumber() const
{
    return ui->lePhone->text();
}

void PageTeachersForm::setPhoneNumber(const QString &phoneNumber)
{
    ui->lePhone->setText(phoneNumber);
}

void PageTeachersForm::setupConnections()
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
