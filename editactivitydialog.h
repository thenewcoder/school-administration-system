#ifndef EDITACTIVITYDIALOG_H
#define EDITACTIVITYDIALOG_H

#include <QDialog>
#include "activity.h"

namespace Ui {
class EditActivityDialog;
}

class EditActivityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditActivityDialog(QWidget *parent = 0, const QString &title = "", bool isEditMode = false);
    ~EditActivityDialog();

    Activity getActivity() const;
    void setActivity(const Activity &activity);

private slots:
    void onProfileHasChanged();

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

    void setupConnections();
    void setupDetectEditConnections();
    void toggleOKButton(bool state);

private:
    Ui::EditActivityDialog *ui;

    bool mEditMode;

    Activity mActivity;
};

#endif // EDITACTIVITYDIALOG_H
