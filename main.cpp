#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include "wizardsetup.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // check if settings.ini exists
    if (!Settings::instance().settingsExists())
    {
        // take user through the wizard
        WizardSetup setup;
        if (setup.exec() == QWizard::Accepted)
        {
            qDebug() << "Settings setup properly";
        }
        else
        {
            return 0;
        }
    }

    w.show();
    return a.exec();
}
