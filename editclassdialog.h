#ifndef EDITCLASSDIALOG_H
#define EDITCLASSDIALOG_H

#include <QDialog>

namespace Ui {
class EditClassDialog;
}

class EditClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditClassDialog(QWidget *parent = 0);
    ~EditClassDialog();

private:
    Ui::EditClassDialog *ui;
};

#endif // EDITCLASSDIALOG_H
