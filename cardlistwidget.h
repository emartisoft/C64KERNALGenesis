#pragma once

#include <QWidget>
#include <QList>
#include <QLabel>
#include "carditem.h"

class QScrollArea;
class QVBoxLayout;
class QLineEdit;
class CardWidget;

/**
 * CardListWidget
 * ──────────────────────────────────────────────────────────────
 * Kartları dikey liste halinde gösteren, arama destekli widget.
 *
 * Kullanım:
 *   CardListWidget *list = new CardListWidget(this);
 *   list->addCard({1, ":/img.png", "Ad", "Kısa yorum", "Uzun detay"});
 *   connect(list, &CardListWidget::cardClicked, this, &MyClass::onCardClicked);
 */
class CardListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CardListWidget(QWidget *parent = nullptr);

    void addCard(const CardItem &item);
    void addCards(const QList<CardItem> &items);
    void clearCards();

signals:
    void cardClicked(const CardItem &item);

private slots:
    void onSearchChanged(const QString &text);

private:
    void rebuildList(const QString &filter = {});

    QLineEdit   *m_searchEdit  = nullptr;
    QScrollArea *m_scrollArea  = nullptr;
    QWidget     *m_container   = nullptr;
    QVBoxLayout *m_listLayout  = nullptr;
    QLabel      *m_infocount   = nullptr;

    QList<CardItem>   m_allItems;
    QList<CardWidget*> m_cardWidgets;
};
