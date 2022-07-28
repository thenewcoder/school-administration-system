#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QSplashScreen>
#include <QTimer>
#include <QThread>
#include <QDebug>

#include "wizardsetup.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    // hopefully fix some scaling issues
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    a.setStyle("fusion");  // the docs suggested using the fusion style for DPI scaling issues

    MainWindow w;

    // prepare the translator
    QTranslator *translator = Settings::instance().getTranslator();
    qApp->installTranslator(translator);

    // check if settings.ini exists
    if (!Settings::instance().settingsExists()) // no settings.ini exist
    {
        // take user through the wizard
        WizardSetup setup;
        if (setup.exec() != QWizard::Accepted) // if user cancelled then close application
        {
            return 0;
        }
    }
    else // settings already exist
    {
        // get the preferred user language
        QString lang = Settings::instance().language();
        if (lang != "en_US") // other language than english
        {
            translator->load("translations/trans_" + lang);
        }
    }

    QPixmap pixmap("://images/splashscreen.jpg");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    splash.showMessage("Loading files...", Qt::AlignBottom | Qt::AlignCenter);

    QTimer::singleShot(2500, &splash, [&] () {
        w.show();
        splash.finish(&w);
    });

    //splash.finish(&w);
    //w.show();

    return a.exec();
}
