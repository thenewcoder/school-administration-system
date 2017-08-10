#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include "databasemanager.h"
#include "student.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStringListModel>
#include <QLocale>
#include <QBuffer>

EditStudentDialog::EditStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog),
    mDefaultPhoto(true)
{
    ui->setupUi(this);

    // set window title
    setWindowTitle("Student Information");

    // prepare the nationalities combo box
    QStringList countries(tr("Select one"));
    countries << DatabaseManager::instance().nationalities();
    ui->cbNationality->setModel(new QStringListModel(countries));

    // prepare the dormitory combo box
    QStringList dormitories(tr("Select one"));
    dormitories << DatabaseManager::instance().dormitories();
    ui->cbDormitory->setModel(new QStringListModel(dormitories));

    // prepare the busstop combo box
    QStringList busstops(tr("Select one"));
    busstops << DatabaseManager::instance().busstops();
    ui->cbBusStop->setModel(new QStringListModel(busstops));

    setupConnections();
}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::setStudent(const Student &student)
{
    setName(student.name());
    setDateOfBirth(student.dateOfBirth());
    setGender(student.gender());
    setNationality(student.nationality());
    setPassportNumber(student.passportNumber());
    setIdNumber(student.iDNumber());
    setAddress(student.address());
    setStudentPhoneNumber(student.studentPhoneNumber());
    setStudentEmail(student.studentEmail());
    setFathersPhoneNumber(student.fathersPhoneNumber());
    setMothersPhoneNumber(student.mothersPhoneNumber());
    setParentEmail(student.parentsEmail());

    // check whether to display default profile photo or saved photo
    if (!student.photo().isEmpty())
    {
        setPhoto(student.photo());
        mDefaultPhoto = false;
    }
    else
        mDefaultPhoto = true;

    setDormitory(student.dormitory());
    setBusstop(student.busstop());

    // prepare the classes list view
    QStringList classesTaken = DatabaseManager::instance().classesTaken(student.getId());
    ui->lvClassesTaken->setModel(new QStringListModel(classesTaken));
}

Student EditStudentDialog::getStudent() const
{
    Student student;
    student.setName(name());
    student.setDateOfBirth(dateOfBirth());
    student.setGender(gender());
    student.setNationality(nationality());
    student.setPassportNumber(passportNumber());
    student.setIDNumber(idNumber());
    student.setAddress(address());
    student.setStudentPhoneNumber(studentPhoneNumber());
    student.setStudentEmail(studentEmail());
    student.setFathersPhoneNumber(fathersPhoneNumber());
    student.setMothersPhoneNumber(mothersPhoneNumber());
    student.setParentsEmail(parentEmail());

    if (!mDefaultPhoto)
        student.setPhoto(photo());

    student.setDormitory(dormitory());
    student.setBusstop(busstop());

    return student;
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

QString EditStudentDialog::dateOfBirth() const
{
    return QLocale("en_US").toString(ui->deBirthDate->date(), "MMM d, yyyy");
}

void EditStudentDialog::setDateOfBirth(const QString &date)
{
    QDate d = QLocale("en_US").toDate(date, "MMM d, yyyy");
    ui->deBirthDate->setDate(d);
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
    QString text = ui->cbNationality->currentText();
    if (text.isEmpty() || ui->cbNationality->currentIndex() == 0)
        return "";
    return text;
}

void EditStudentDialog::setNationality(const QString &nationality)
{
    QString text = !nationality.isEmpty() ? nationality : "Select one";
    ui->cbNationality->setCurrentText(text);
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

QByteArray EditStudentDialog::photo() const
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    ui->lblStudentPhoto->pixmap()->save(&buffer, "PNG");
    return bytes;
}

void EditStudentDialog::setPhoto(const QByteArray &photo)
{
    QPixmap p;
    p.loadFromData(photo);
    ui->lblStudentPhoto->setPixmap(p);
}

QString EditStudentDialog::dormitory() const
{
    if (ui->cbDormitory->currentIndex() == 0)
        return QString("");
    return ui->cbDormitory->currentText();
}

void EditStudentDialog::setDormitory(const QString &dormitory)
{
    if (dormitory.isEmpty())
        ui->cbDormitory->setCurrentIndex(0);
    else
        ui->cbDormitory->setCurrentText(dormitory);
}

QString EditStudentDialog::busstop() const
{
    if (ui->cbBusStop->currentIndex() == 0)
        return QString("");
    return ui->cbBusStop->currentText();
}

void EditStudentDialog::setBusstop(const QString &busstop)
{
    if (busstop.isEmpty())
        ui->cbBusStop->setCurrentIndex(0);
    else
        ui->cbBusStop->setCurrentText(busstop);
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
            QImage photo = img.scaled(150, 150, Qt::KeepAspectRatio);
            ui->lblStudentPhoto->setPixmap(QPixmap::fromImage(photo));
            mDefaultPhoto = false;
        }
    });

    connect(ui->btnRemove, &QPushButton::clicked, [this] () {
       ui->lblStudentPhoto->setPixmap(QPixmap(":/images/user_profile.png"));
       mDefaultPhoto = true;
    });
}

