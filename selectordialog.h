#ifndef SELECTORDIALOG_H
#define SELECTORDIALOG_H

#include <QDialog>

namespace Ui {
class SelectorDialog;
}

class QStringListModel;

class SelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectorDialog(const QString &title, QStringList &listAll,
                            const QStringList &listChosen, QWidget *parent = 0);
    ~SelectorDialog();

    QStringList getItems() const;

private:
    void setupConnections();

private:
    Ui::SelectorDialog *ui;

    QStringListModel *mModelAll;
    QStringListModel *mModelChosen;
};

#endif // SELECTORDIALOG_H
