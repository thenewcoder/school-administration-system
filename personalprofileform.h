#ifndef PERSONALPROFILEFORM_H
#define PERSONALPROFILEFORM_H

#include <QWidget>
#include "user.h"

namespace Ui {
class PersonalProfileForm;
}

class PersonalProfileForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalProfileForm(QWidget *parent = 0);
    ~PersonalProfileForm();

signals:
    void notifyFullnameChanged(const QString &name);

public slots:
    void setupUser();

private slots:
    void onProfileHasChanged();
    void onPasswordHasChanged();

private:
    void setupConnections();
    void toggleSaveButton(bool state);

private:
    Ui::PersonalProfileForm *ui;

    User mUser;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // PERSONALPROFILEFORM_H
