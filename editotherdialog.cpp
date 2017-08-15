#include "editotherdialog.h"
#include "ui_editotherdialog.h"

EditOtherDialog::EditOtherDialog(const QString &title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditOtherDialog)
{
    ui->setupUi(this);

    setTitle(title);
}

EditOtherDialog::~EditOtherDialog()
{
    delete ui;
}

QString EditOtherDialog::name() const
{
    return ui->leName->text();
}

void EditOtherDialog::setName(const QString &name)
{
    ui->leName->setText(name);
}

QString EditOtherDialog::comment() const
{
    return ui->pteComments->toPlainText();
}

void EditOtherDialog::setComment(const QString &comment)
{
    ui->pteComments->setPlainText(comment);
}

void EditOtherDialog::setTitle(const QString &title)
{
    setWindowTitle(title);
}
