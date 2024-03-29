﻿#include "editteacherdialog.h"
#include "ui_editteacherdialog.h"

#include "databasemanager.h"
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
    mDefaultPhoto(true),
    mEditMode(false)
{
    ui->setupUi(this);

    // set dialog window title
    setWindowTitle("Teacher Information");

    // prepare the nationality combo box
    QStringList countries("Select one");
    countries << DatabaseManager::instance().nationalities();
    ui->cbNationality->setModel(new QStringListModel(countries));

    ui->cbGender->setEditable(true);
    ui->cbGender->lineEdit()->setPlaceholderText(tr("Choose Gender..."));
    ui->cbGender->addItems(QStringList{tr("Male"), tr("Female")});
    ui->cbGender->setCurrentIndex(-1);

    // prepare the list view classes model
    ui->lvClasses->setModel(mModelClasses);

    // limit characters for the phone number
    QRegExp phoneRegx("[-+() 0-9]{14}");
    QRegExpValidator *phoneValidator = new QRegExpValidator(phoneRegx, this);
    ui->lePhone->setValidator(phoneValidator);

    setupConnections();

    // disable the OK button
    toggleSaveButton(false);
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

    // save a copy of the teacher
    mTeacher = teacher;

    // remember the classes taught
    mTeacher.setClassesTaught(classes);

    // setup the edit mode connections
    setupDetectEditConnections();
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
    int currentIndex = ui->cbGender->currentIndex();
    if (currentIndex == 0)
        return QString("0");
    else if (currentIndex == 1)
        return QString("1");
    return QString("");
}

void EditTeacherDialog::setGender(const QString &gender)
{
    if (gender == "0")
        ui->cbGender->setCurrentIndex(0);
    else if (gender == "1")
        ui->cbGender->setCurrentIndex(1);
    else
        ui->cbGender->setCurrentIndex(-1);
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

void EditTeacherDialog::setEditMode(bool state)
{
    mEditMode = state;
}

void EditTeacherDialog::setWidgetsEnabled(bool state)
{
    ui->btnEditClasses->setEnabled(state);
    ui->btnAddPhoto->setEnabled(state);
    ui->btnRemove->setEnabled(state);
    ui->cbGender->setEnabled(state);
    ui->cbNationality->setEnabled(state);
    ui->leName->setEnabled(state);
    ui->lePreferredName->setEnabled(state);
    ui->lePhone->setEnabled(state);
    ui->teAddress->setEnabled(state);

    // toggle some elements visibility when in view mode
    ui->buttonBox->button(QDialogButtonBox::Save)->setVisible(state);
    ui->btnAddPhoto->setVisible(state);
    ui->btnRemove->setVisible(state);
    ui->btnEditClasses->setVisible(state);
}

void EditTeacherDialog::setupConnections()
{
    // add connection to check if the save button should be enabled or disabled
    connect(ui->leName, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));

    // add a new photo
    connect(ui->btnAddPhoto, &QPushButton::clicked, this, [this] () {
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

            onProfileHasChanged();
        }
    });

    // remove the current photo
    connect(ui->btnRemove, &QPushButton::clicked, this, [this] () {
       ui->lblPhoto->setPixmap(QPixmap(":/images/user_profile.png"));
       mDefaultPhoto = true;

       onProfileHasChanged();
    });

    // edit the classes taught
    connect(ui->btnEditClasses, &QPushButton::clicked, this, [this] () {
        QStringList all = DatabaseManager::instance().classes();
        SelectorDialog edit(tr("Edit Teacher Classes"),
                            all,
                            mModelClasses->stringList(),
                            this);

        if (edit.exec() == QDialog::Accepted)
        {
            // add the classes to list view
            mModelClasses->setStringList(edit.getItems());

            onProfileHasChanged();
        }
    });
}

void EditTeacherDialog::setupDetectEditConnections()
{
    connect(ui->lePreferredName, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->cbGender, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->cbNationality, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->teAddress, SIGNAL(textChanged()), this, SLOT(onProfileHasChanged()));
    connect(ui->lePhone, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
}

void EditTeacherDialog::toggleSaveButton(bool state)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(state);
}

void EditTeacherDialog::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QDialog::changeEvent(e);
}

void EditTeacherDialog::on_buttonBox_accepted()
{
    accept();
}

void EditTeacherDialog::on_buttonBox_rejected()
{
    reject();
}

void EditTeacherDialog::onProfileHasChanged()
{
    bool hasChanged = false;

    // if a teacher name has been entered, enable save button
    if (!ui->leName->text().isEmpty() && !mEditMode)
        hasChanged = true;
    else if (mEditMode) // if we are editing
    {
        if (mTeacher.name() != name())
            hasChanged = true;
        else if (mTeacher.preferredName() != preferredName())
            hasChanged = true;
        else if (mTeacher.gender() != gender())
            hasChanged = true;
        else if (mTeacher.nationality() != nationality())
            hasChanged = true;
        else if (mTeacher.address() != address())
            hasChanged = true;
        else if (mTeacher.phoneNumber() != phoneNumber())
            hasChanged = true;
        else if ((mTeacher.photo().isEmpty() != mDefaultPhoto) &&
                 mTeacher.photo() != photo())
            hasChanged = true;

        // evaluate the classes taught list - any better way?
        if (mTeacher.classesTaught().length() != mModelClasses->stringList().length())
            hasChanged = true;
        else // same length but values might be different
        {
            QStringList tmp = mTeacher.classesTaught();

            for (QString &v : mModelClasses->stringList())
            {
                if (tmp.contains(v)) // if found in tmp remove it
                    tmp.removeOne(v);
            }

            // if length of tmp is not zero, a change has been made
            if (!tmp.isEmpty())
                hasChanged = true;
        }
    }

    toggleSaveButton(hasChanged);
}
