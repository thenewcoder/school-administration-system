#ifndef EDITACTIVITYDIALOG_H
#define EDITACTIVITYDIALOG_H

#include <QDialog>

namespace Ui {
class EditActivityDialog;
}

class Activity;

class EditActivityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditActivityDialog(QWidget *parent = 0, const QString &title = "");
    ~EditActivityDialog();

    Activity getActivity() const;
    void setActivity(const Activity &activity);

private:
    QString code() const;
    void setCode(const QString &code);

    QString activityName() const;
    void setActivityName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString advisor() const;
    void setAdvisor(const QString &advisor);

    QString membershipLimit() const;
    void setMembershipLimit(const QString &limit);

private:
    Ui::EditActivityDialog *ui;
};

#endif // EDITACTIVITYDIALOG_H
