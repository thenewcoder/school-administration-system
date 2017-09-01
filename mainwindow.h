#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class AdminMenuForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupConnections();

    void setupNewAdminForm();

    QString username() const;
    QString password() const;

signals:
    void notifyUserLogin();

private:
    Ui::MainWindow *ui;

    AdminMenuForm *adminMenuForm;

    // QWidget interface
protected:
    virtual void changeEvent(QEvent *e) override;
};

#endif // MAINWINDOW_H
