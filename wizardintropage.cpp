#include "wizardintropage.h"

#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

WizardIntroPage::WizardIntroPage(QWidget *parent)
    : QWizardPage(parent)
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
    cbLanguage->addItem("English");
    cbLanguage->addItem("Chinese");
    cbLanguage->addItem("Korean");
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
}
