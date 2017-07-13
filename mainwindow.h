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

    QString username() const;
    QString password() const;

private:
    Ui::MainWindow *ui;

    AdminMenuForm *adminMenuForm;
};

#endif // MAINWINDOW_H
