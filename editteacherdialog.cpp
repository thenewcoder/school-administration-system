#include "editteacherdialog.h"
#include "ui_editteacherdialog.h"

#include "databasemanager.h"
#include "teacher.h"
#include "selectordialog.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStringListModel>
#include <QBuffer>
#include <QDebug>

EditTeacherDialog::EditTeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTeacherDialog),
    mModelClasses(new QStringListModel(this)),
    mTeacherId(),
    mDefaultPhoto(true)
{
    ui->setupUi(this);

    // set dialog window title
    setWindowTitle("Teacher Information");

    // prepare the nationality combo box
    QStringList countries("Select one");
    countries << DatabaseManager::instance().nationalities();
    ui->cbNationality->setModel(new QStringListModel(countries));

    // prepare the list view classes model
    ui->lvClasses->setModel(mModelClasses);

    setupConnections();
}

EditTeacherDialog::~EditTeacherDialog()
{
    delete ui;
}

void EditTeacherDialog::setTeacher(const Teacher &teacher)
{
    setName(teacher.name());
    setPreferredName(teacher.preferredName());
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

    // prepare the list view of classes taught
    QStringList classes = DatabaseManager::instance().classesTaught(getId());
    setClassesTaught(classes);
}

Teacher EditTeacherDialog::getTeacher() const
{
    Teacher teacher;
    teacher.setName(name());
    teacher.setPreferredName(preferredName());
    teacher.setGender(gender());
    teacher.setNationality(nationality());
    teacher.setAddress(address());
    teacher.setPhoneNumber(phoneNumber());

    if (!mDefaultPhoto)
        teacher.setPhoto(photo());

    // set the classes taught
    teacher.setClassesTaught(classesTaught());

    return teacher;
}

QString EditTeacherDialog::getId() const
{
    return mTeacherId;
}

void EditTeacherDialog::setId(const QString &id)
{
    mTeacherId = id;
}

QString EditTeacherDialog::name() const
{
    return ui->leName->text();
}

void EditTeacherDialog::setName(const QString &name)
{
    ui->leName->setText(name);
}

QString EditTeacherDialog::preferredName() const
{
    return ui->lePreferredName->text();
}

void EditTeacherDialog::setPreferredName(const QString &preferredName)
{
    ui->lePreferredName->setText(preferredName);
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
    QString text = ui->cbNationality->currentText();
    if (text.isEmpty() || ui->cbNationality->currentIndex() == 0)
        return "";
    return text;
}

void EditTeacherDialog::setNationality(const QString &nationality)
{
    QString text = !nationality.isEmpty() ? nationality : tr("Select one");
    ui->cbNationality->setCurrentText(text);
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

QStringList EditTeacherDialog::classesTaught() const
{
    return mModelClasses->stringList();
}

void EditTeacherDialog::setClassesTaught(const QStringList &classes)
{
    mModelClasses->setStringList(classes);
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

    connect(ui->btnEditClasses, &QPushButton::clicked, [this] () {
        QStringList all = DatabaseManager::instance().classes();
        SelectorDialog edit(tr("Edit Teacher Classes"),
                            all,
                            DatabaseManager::instance().classesTaught(getId()),
                            this);

        if (edit.exec() == QDialog::Accepted)
        {
            // add the classes to list view
            mModelClasses->setStringList(edit.getItems());
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
