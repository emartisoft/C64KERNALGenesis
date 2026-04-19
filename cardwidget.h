#pragma once

#include <QWidget>
#include "carditem.h"
#include "gifwidget.h"

class QLabel;

/**
 * CardWidget
 *
 * Tıklanınca clicked(CardItem) sinyali yayar.
 */
class CardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CardWidget(const CardItem &item, QWidget *parent = nullptr);

    const CardItem &cardItem() const { return m_item; }

signals:
    void clicked(const CardItem &item);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setupUi();
    void setHovered(bool hovered);

    CardItem m_item;
    bool     m_hovered = false;

    GifWidget *m_thumbLabel  = nullptr;
    QLabel *m_nameLabel   = nullptr;
    QLabel *m_commentLabel = nullptr;
    QLabel *m_statusLabel = nullptr;
};
