#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

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
    QTranslator *translator = new QTranslator;
    Settings::instance().addTranslator(translator);
    qApp->installTranslator(translator);

    // check if settings.ini exists
    if (!Settings::instance().settingsExists()) // no settings.ini exist
    {
        // take user through the wizard
        WizardSetup setup(translator);
        if (setup.exec() != QWizard::Accepted) // if user cancelled then close application
        {
            // delete pointers
            delete translator;

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

    w.show();
    int return_code = a.exec();

    // delete pointers
    delete translator;

    return return_code;
}
