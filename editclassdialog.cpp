#include "editclassdialog.h"
#include "ui_editclassdialog.h"

EditClassDialog::EditClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditClassDialog)
{
    ui->setupUi(this);
}

EditClassDialog::~EditClassDialog()
{
    delete ui;
}
