#include "editactivitydialog.h"
#include "ui_editactivitydialog.h"

#include <QPushButton>
#include <QRegExpValidator>
#include "databasemanager.h"

EditActivityDialog::EditActivityDialog(QWidget *parent, const QString &title, bool isEditMode) :
    QDialog(parent),
    ui(new Ui::EditActivityDialog),
    mEditMode(isEditMode)
{
    ui->setupUi(this);

    // set the window title
    if (!title.isEmpty())
    {
        setWindowTitle(title);
    }

    // setup the teacher advisor combo box
    QStringList advisors;
    advisors << "" << DatabaseManager::instance().teachers();
    ui->cbAdvisor->addItems(advisors);

    // setup a validator for the membership limit line edit, between 1 - 9999
    QValidator *validator = new QRegExpValidator(QRegExp("[1-9][0-9]{1,3}"), this);
    ui->leMembership->setValidator(validator);

    setupConnections();

    // start with OK button disabled
    toggleOKButton(false);
}

EditActivityDialog::~EditActivityDialog()
{
    delete ui;
}

Activity EditActivityDialog::getActivity() const
{
    Activity activity;
    activity.setCode(code());
    activity.setName(activityName());
    activity.setDescription(description());
    activity.setAdvisor(advisor());
    activity.setLimit(membershipLimit());
    return activity;
}

void EditActivityDialog::setActivity(const Activity &activity)
{
    setCode(activity.code());
    setActivityName(activity.name());
    setDescription(activity.description());
    setAdvisor(activity.advisor());
    setMembershipLimit(activity.limit());

    // save a copy of the activity object
    mActivity = activity;

    // setup the connections for edit mode
    setupDetectEditConnections();
}

void EditActivityDialog::onProfileHasChanged()
{
    bool hasChanged = false;

    if (!ui->leName->text().isEmpty() && !mEditMode)
        hasChanged = true;
    else if (mEditMode)
    {
        if (mActivity.code() != code())
            hasChanged = true;
        else if (mActivity.name() != activityName())
            hasChanged = true;
        else if (mActivity.description() != description())
            hasChanged = true;
        else if (mActivity.advisor() != advisor())
            hasChanged = true;
        else if (mActivity.limit() != membershipLimit())
            hasChanged = true;
    }
    toggleOKButton(hasChanged);
}

void EditActivityDialog::setupConnections()
{
    // setup connection to determine if the OK button should be enabled
    connect(ui->leName, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
}

void EditActivityDialog::setupDetectEditConnections()
{
    // setup connections for edit mode
    connect(ui->leCode, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->pteDescription, SIGNAL(textChanged()), this, SLOT(onProfileHasChanged()));
    connect(ui->cbAdvisor, SIGNAL(currentTextChanged(QString)), this, SLOT(onProfileHasChanged()));
    connect(ui->leMembership, SIGNAL(textEdited(QString)), this, SLOT(onProfileHasChanged()));
}

QString EditActivityDialog::code() const
{
    return ui->leCode->text();
}

void EditActivityDialog::setCode(const QString &code)
{
    ui->leCode->setText(code);
}

QString EditActivityDialog::activityName() const
{
    return ui->leName->text();
}

void EditActivityDialog::setActivityName(const QString &name)
{
    ui->leName->setText(name);
}

QString EditActivityDialog::description() const
{
    return ui->pteDescription->toPlainText();
}

void EditActivityDialog::setDescription(const QString &description)
{
    ui->pteDescription->setPlainText(description);
}

QString EditActivityDialog::advisor() const
{
    return ui->cbAdvisor->currentText();
}

void EditActivityDialog::setAdvisor(const QString &advisor)
{
    ui->cbAdvisor->setCurrentText(advisor);
}

QString EditActivityDialog::membershipLimit() const
{
    return ui->leMembership->text();
}

void EditActivityDialog::setMembershipLimit(const QString &limit)
{
    ui->leMembership->setText(limit);
}

void EditActivityDialog::toggleOKButton(bool state)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(state);
}
