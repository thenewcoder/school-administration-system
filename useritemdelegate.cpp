#include "useritemdelegate.h"

UserItemDelegate::UserItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

QString UserItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale)

    QString text("");
    int userType = -1;

    if (!value.toString().isEmpty())
        userType = value.toInt();

    switch(userType)
    {
    case 1:
        text = tr("Administrator");
        break;
    case 2:
        text = tr("Teacher");
        break;
    default:
        break;
    }
    return text;
}
