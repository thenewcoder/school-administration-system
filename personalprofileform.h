#ifndef PERSONALPROFILEFORM_H
#define PERSONALPROFILEFORM_H

#include <QWidget>
#include <QHash>
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

public slots:
    void setupUser();

private slots:
    void onUsernameChanged(const QString &change);
    void onFullnameChanged(const QString &change);

private:
    void setupConnections();
    void toggleSaveButton(bool state);

private:
    Ui::PersonalProfileForm *ui;

    User user;

    bool mSettingsChanged;
    QHash<QString, QString> mPendingChanges;
};

#endif // PERSONALPROFILEFORM_H
