#ifndef SYSTEMSETTINGSFORM_H
#define SYSTEMSETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SystemSettingsForm;
}

class SystemSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingsForm(QWidget *parent = 0);
    ~SystemSettingsForm();

    void setLanguage(const QString &locale);

private:
    void setupConnections();

private slots:
    void onLanguageChanged(int index);

signals:
    void notifyLanguageChanged();

private:
    Ui::SystemSettingsForm *ui;

    QString mLanguage;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // SYSTEMSETTINGSFORM_H
