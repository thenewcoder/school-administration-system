#ifndef USERITEMDELEGATE_H
#define USERITEMDELEGATE_H

#include <QStyledItemDelegate>

class UserItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit UserItemDelegate(QObject *parent = nullptr);

    // QStyledItemDelegate interface
public:
    QString displayText(const QVariant &value, const QLocale &locale) const override;
};

#endif // USERITEMDELEGATE_H
