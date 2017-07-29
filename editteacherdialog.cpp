#include "editteacherdialog.h"
#include "ui_editteacherdialog.h"

#include "databasemanager.h"
#include "teacher.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStringListModel>
#include <QBuffer>

EditTeacherDialog::EditTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTeacherDialog),
    mDefaultPhoto(true)
{
    ui->setupUi(this);

    QStringList countries("Select one");
    countries << DatabaseManager::instance().nationalities();
    countries.removeAt(1);
    ui->cbNationality->setModel(new QStringListModel(countries));

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

    // check whether to display default profile photo or saved photo
    if (!teacher.photo().isEmpty())
    {
        setPhoto(teacher.photo());
        mDefaultPhoto = false;
    }
    else
        mDefaultPhoto = true;
}

Teacher EditTeacherDialog::getTeacher() const
{
    Teacher teacher;
    teacher.setName(name());
    teacher.setGender(gender());
    teacher.setNationality(nationality());
    teacher.setAddress(address());
    teacher.setPhoneNumber(phoneNumber());

    if (!mDefaultPhoto)
        teacher.setPhoto(photo());

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

QByteArray EditTeacherDialog::photo() const
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    ui->lblPhoto->pixmap()->save(&buffer, "PNG");
    return bytes;
}

void EditTeacherDialog::setPhoto(const QByteArray &photo)
{
    QPixmap p;
    p.loadFromData(photo);
    ui->lblPhoto->setPixmap(p);
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
            QImage photo = img.scaled(150, 150, Qt::KeepAspectRatio);
            ui->lblPhoto->setPixmap(QPixmap::fromImage(photo));
            mDefaultPhoto = false;
        }
    });

    connect(ui->btnRemove, &QPushButton::clicked, [this] () {
       ui->lblPhoto->setPixmap(QPixmap(":/images/user_profile.png"));
       mDefaultPhoto = true;
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
