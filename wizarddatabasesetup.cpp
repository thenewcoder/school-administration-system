#include "wizarddatabasesetup.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>

WizardDatabaseSetup::WizardDatabaseSetup(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Database Setup"));

    // setup the database type
    lblDatabaseType = new QLabel(tr("Database Type:"));

    cbDatabaseDrivers = new QComboBox;
    cbDatabaseDrivers->addItem("SQLite");
    cbDatabaseDrivers->setFixedWidth(100);

    // setup the radio buttons
    btnNewDatabase = new QRadioButton(tr("Create a New Database"));
    btnExistingDatabase = new QRadioButton(tr("Use an Existing Database"));
    btnNewDatabase->setChecked(true);

    // setup the groupbox for the database creation types
    gbGroupBox = new QGroupBox(tr("Database"));

    // prepare the group box layout and add it to the group box
    QVBoxLayout *groupboxLayout = new QVBoxLayout;
    groupboxLayout->addWidget(btnNewDatabase);
    groupboxLayout->addWidget(btnExistingDatabase);
    gbGroupBox->setLayout(groupboxLayout);

    // setup the default location check box button
    chbDefaultLocation = new QCheckBox(tr("Default Location (Recommended)"));
    chbDefaultLocation->setChecked(true);

    // setup the location selection line edit and button
    lblLocation = new QLabel(tr("Location:"));
    leLocation = new QLineEdit;
    btnChangeLocation = new QPushButton("...");
    btnChangeLocation->setFixedWidth(50);

    // prepare main layout and add the widgets
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lblDatabaseType, 0, 0);
    layout->addWidget(cbDatabaseDrivers, 0, 1, 1, 1);
    layout->addWidget(gbGroupBox, 1, 0, 1, 4);
    layout->addWidget(chbDefaultLocation, 2, 0, 1, 4);
    layout->addWidget(lblLocation, 3, 0);
    layout->addWidget(leLocation, 3, 1);
    layout->addWidget(btnChangeLocation, 3, 2);
    layout->setVerticalSpacing(10);

    setLayout(layout);

    setupConnections();

    // register fields
    registerField("databasedriver", cbDatabaseDrivers, "currentText");
    registerField("defaultLocation", chbDefaultLocation);
    registerField("newdatabase", btnNewDatabase);
    registerField("location", leLocation);

    // disable the line edit and button on startup
    leLocation->setEnabled(false);
    btnChangeLocation->setEnabled(false);
}

void WizardDatabaseSetup::setupConnections()
{
    // connections needed for the isComplete() to work properly
    connect(leLocation, &QLineEdit::textChanged, this, &WizardDatabaseSetup::completeChanged);

    // default location checkbox button
    connect(chbDefaultLocation, &QCheckBox::toggled, [this] (bool toggled) {
        if (toggled)
        {
            leLocation->setEnabled(false);
            btnChangeLocation->setEnabled(false);
        }
        else
        {
            leLocation->setEnabled(true);
            btnChangeLocation->setEnabled(true);
        }
    });

    // existing database radio button
    connect(btnExistingDatabase, &QRadioButton::clicked, [this] (bool clicked) {
        if (clicked)
        {
            chbDefaultLocation->setChecked(false);
            chbDefaultLocation->setEnabled(false);

        }
    });

    // new database radio button
    connect(btnNewDatabase, &QRadioButton::clicked, [this] (bool clicked) {
        if (clicked)
        {
            chbDefaultLocation->setEnabled(true);
            chbDefaultLocation->setChecked(true);
        }
    });

    // change location button
    connect(btnChangeLocation, &QPushButton::clicked, [this] () {
        if (btnNewDatabase->isChecked())
        {
            QFileDialog dialog(this);
            dialog.setWindowTitle(tr("Choose a Directory..."));
            dialog.setFileMode(QFileDialog::Directory);
            dialog.setOption(QFileDialog::ShowDirsOnly, true);

            if (dialog.exec() == QFileDialog::Accepted)
            {
                QString path = dialog.directory().absolutePath();
                leLocation->setText(path);
            }

        }
        else if (btnExistingDatabase->isChecked())
        {
            QFileDialog dialog(this);
            dialog.setWindowTitle(tr("Choose Existing Database..."));
            dialog.setFileMode(QFileDialog::ExistingFile);
            dialog.setViewMode(QFileDialog::Detail);

            if (dialog.exec() == QFileDialog::Accepted)
            {
                QString file = dialog.selectedFiles().first();
                leLocation->setText(file);
                // TODO: add a database test later
            }
        }
    });
}

bool WizardDatabaseSetup::isComplete() const
{
    return (!chbDefaultLocation->isChecked() && !leLocation->text().isEmpty())
            || chbDefaultLocation->isChecked();
}
