#include "coloritemdelegate.h"
#include <QPainter>
#include <QApplication>

ColorItemDelegate::ColorItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ColorItemDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    painter->save();

    QColor color = index.data(Qt::UserRole).value<QColor>();
    QString text = index.data(Qt::DisplayRole).toString();

    QRect rect = option.rect;

    // Arka planı HER ZAMAN sabit beyaz yap
    painter->fillRect(rect, Qt::white);

    // Renk kutusu
    QRect colorRect = QRect(rect.left() + 4, rect.top() + 4, 24, rect.height() - 8);
    painter->fillRect(colorRect, color);
    painter->setPen(Qt::black);
    painter->drawRect(colorRect);

    bool hover = option.state & QStyle::State_MouseOver;

    QFont font = option.font;
    if (hover)
        font.setBold(true);

    painter->setFont(font);

    // Yazı
    QRect textRect = QRect(colorRect.right() + 8, rect.top(),
                           rect.width() - colorRect.width() - 16,
                           rect.height());

    painter->setPen(Qt::black);
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);

    painter->restore();
}

QSize ColorItemDelegate::sizeHint(const QStyleOptionViewItem &,
                                  const QModelIndex &) const
{
    return QSize(120, 30);
}
