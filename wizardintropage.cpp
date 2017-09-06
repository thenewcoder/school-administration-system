#include "wizardintropage.h"

#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTranslator>
#include <QApplication>
#include "wizardsetup.h"

WizardIntroPage::WizardIntroPage(QWidget *parent)
    : QWizardPage(parent)
    , translator(qobject_cast<WizardSetup *>(parent)->mTranslator)
    , mLangIndex(0)
{
    setTitle(tr("Welcome"));

    // setup the intro text label
    lblIntroText = new QLabel(tr("This wizard will help you to set up the database "
                          "and the user profile needed to use this software properly. "
                          "Please fill in the information on the next couple of pages."),
                           this);

    lblIntroText->setWordWrap(true);

    // setup the language label and combo box
    lblLanguage = new QLabel(tr("Choose Language"));

    cbLanguage = new QComboBox;
    QStringList languages;
    languages << tr("English") << tr("Chinese");
    cbLanguage->addItems(languages);
    //cbLanguage->addItem(tr("Korean"));
    cbLanguage->setFixedWidth(100);

    // prepare the layout for the language section
    QHBoxLayout *lang_layout = new QHBoxLayout;
    lang_layout->addWidget(lblLanguage);
    lang_layout->setSpacing(20);
    lang_layout->addWidget(cbLanguage);
    lang_layout->addSpacerItem(new QSpacerItem(30, 5, QSizePolicy::Expanding));

    // prepare the page layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lblIntroText);
    layout->addSpacing(20);
    layout->addLayout(lang_layout);
    setLayout(layout);

    // register fields
    registerField("language", cbLanguage, "currentText");

    // setup connection for the combo box
    //void (QComboBox::* activatedOverloadPtr)(int index) = &QComboBox::currentIndexChanged;
    connect(cbLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));
}

void WizardIntroPage::changeLanguage(int index)
{
    // disonnect the combobox signal so it won't be called when translating
    disconnect(cbLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));
    if (index == 0) // English
    {
        translator->load("translations/trans_en_US");
    }
    else if (index == 1) // Chinese
    {
        translator->load("translations/trans_zh_CN");
    }
    // remember the selected index
    mLangIndex = index;
}

void WizardIntroPage::resetComboBox()
{
    // set the new index to the previously selected index
    cbLanguage->setCurrentIndex(mLangIndex);

    // activate the connection again
    connect(cbLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLanguage(int)));
}

void WizardIntroPage::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        setTitle(translator->translate("WizardIntroPage", "Welcome"));
        lblLanguage->setText(translator->translate("WizardIntroPage", "Choose Language"));
        lblIntroText->setText(translator->translate("WizardIntroPage", "This wizard will help you to set up the database "
                                                                       "and the user profile needed to use this software properly. "
                                                                       "Please fill in the information on the next couple of pages."));

        // translate the combo box texts - better way?
        cbLanguage->clear();
        cbLanguage->addItem(translator->translate("WizardIntroPage", "English"));
        cbLanguage->addItem(translator->translate("WizardIntroPage", "Chinese"));
        resetComboBox(); // return functionality to the combo box
    }
}
