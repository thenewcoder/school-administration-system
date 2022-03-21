#include "selectordialog.h"
#include "ui_selectordialog.h"

#include <QStringListModel>
#include <QDebug>

SelectorDialog::SelectorDialog(const QString &title, QStringList &listAll, const QStringList &listChosen, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectorDialog),
    mModelAll(new QStringListModel(this)),
    mModelChosen(new QStringListModel(this))
{
    ui->setupUi(this);

    // set the title of the dialog
    setWindowTitle(title);

    // set up the models
    ui->lvAllSelections->setModel(mModelAll);
    ui->lvChosenSelections->setModel(mModelChosen);

    // remove items from listAll that exist in listChosen
    //QStringList newListAll = listAll.toSet().subtract(listChosen.toSet()).toList();
    for (auto &i : listChosen)
    {
        listAll.removeOne(i);
    }

    // populate the mModelAll with the string list
    if (listAll.count("") != 1)
    {
        mModelAll->setStringList(listAll);
        mModelAll->sort(0);
    }

    // populate the chosen list view
    if (listChosen.count("") != 1)
    {
        mModelChosen->setStringList(listChosen);
        mModelChosen->sort(0);
    }

    setupConnections();
}

SelectorDialog::~SelectorDialog()
{
    delete ui;
}

QStringList SelectorDialog::getItems() const
{
    return mModelChosen->stringList();
}

void SelectorDialog::setupConnections()
{
    connect(ui->btnAddSelection, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->lvAllSelections->currentIndex();
        if (index.isValid())
        {
            mModelChosen->insertRow(0);
            mModelChosen->setData(mModelChosen->index(0, 0), index.data());
            mModelAll->removeRow(index.row());
            mModelChosen->sort(0);
        }

    });

    connect(ui->btnRemoveSelection, &QPushButton::clicked, [this] () {
        QModelIndex index = ui->lvChosenSelections->currentIndex();
        if (index.isValid())
        {
            mModelAll->insertRow(0);
            mModelAll->setData(mModelAll->index(0, 0), index.data());
            mModelChosen->removeRow(index.row());
            mModelAll->sort(0);
        }
    });
}

void SelectorDialog::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QDialog::changeEvent(e);
}
