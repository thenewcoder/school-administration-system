#ifndef EDITOTHERDIALOG_H
#define EDITOTHERDIALOG_H

#include <QDialog>

namespace Ui {
class EditOtherDialog;
}

class EditOtherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditOtherDialog(const QString &title = QString(), QWidget *parent = 0);
    ~EditOtherDialog();

    QString name() const;
    void setName(const QString &name);

    QString comment() const;
    void setComment(const QString &comment);

    void setTitle(const QString &title);

private:
    Ui::EditOtherDialog *ui;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // EDITOTHERDIALOG_H
