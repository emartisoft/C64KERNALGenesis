#ifndef COLORITEMDELEGATE_H
#define COLORITEMDELEGATE_H

#include <QStyledItemDelegate>

class ColorItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ColorItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

#endif // COLORITEMDELEGATE_H
