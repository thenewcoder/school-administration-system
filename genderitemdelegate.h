#ifndef GENDERITEMDELEGATE_H
#define GENDERITEMDELEGATE_H

#include <QStyledItemDelegate>

class GenderItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit GenderItemDelegate(QObject* parent = nullptr);

    // QStyledItemDelegate interface
public:
    QString displayText(const QVariant &value, const QLocale &locale) const override;
};

#endif // GENDERITEMDELEGATE_H
