#include "editactivitydialog.h"
#include "ui_editactivitydialog.h"

#include "databasemanager.h"
#include "activity.h"

EditActivityDialog::EditActivityDialog(QWidget *parent, const QString &title) :
    QDialog(parent),
    ui(new Ui::EditActivityDialog)
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
