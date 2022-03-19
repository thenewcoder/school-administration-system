#include "genderitemdelegate.h"

GenderItemDelegate::GenderItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QString GenderItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale)

    QString text("");
    int gender = -1;

    if (!value.toString().isEmpty())
        gender = value.toInt();

    switch(gender)
    {
    case 0:
        text = tr("Male");
        break;
    case 1:
        text = tr("Female");
        break;
    default:
        break;
    }
    return text;
}
