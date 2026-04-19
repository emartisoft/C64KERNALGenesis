#include "cardlistwidget.h"
#include "cardwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include <QScrollBar>

CardListWidget::CardListWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // ── Arama kutusu ──────────────────────────────────────────
    auto *searchBar = new QWidget(this);
    searchBar->setFixedHeight(48);
    searchBar->setStyleSheet(/* "background:#f5f5f5;"
                             "border-top:1px solid #e0e0e0;"*/
                             "border-bottom:1px solid #e0e0e0;");

    auto *searchRow = new QHBoxLayout(searchBar);
    searchRow->setContentsMargins(12, 0, 12, 0);
    searchRow->setSpacing(8);

    auto *searchIcon = new QLabel("", searchBar);
    searchIcon->setPixmap(QPixmap(":/res/pictures/find.png"));
    searchIcon->setStyleSheet("background:transparent; font-size:16px;");

    m_searchEdit = new QLineEdit(searchBar);
    m_searchEdit->setPlaceholderText("Type to filter...");
    m_searchEdit->setStyleSheet(
        "QLineEdit {"
        "  background: transparent;"
        "  border: none;"
        "  font-size: 13px;"
        "  color: #212121;"
        "}"
    );
    m_searchEdit->setClearButtonEnabled(true);

    searchRow->addWidget(searchIcon);
    searchRow->addWidget(m_searchEdit, 1);

    connect(m_searchEdit, &QLineEdit::textChanged,
            this, &CardListWidget::onSearchChanged);

    // ── Kart listesi (scroll) ──────────────────────────────────
    m_container = new QWidget;
    //m_container->setStyleSheet("background: #f8f8f8;");

    m_listLayout = new QVBoxLayout(m_container);
    m_listLayout->setContentsMargins(8, 8, 8, 8);
    m_listLayout->setSpacing(6);
    m_listLayout->addStretch();   // kartları üstten iter

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidget(m_container);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "  width: 6px; background: transparent;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background: #c0c0c0; border-radius: 3px; min-height: 24px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "  height: 0;"
        "}"
    );

    m_infocount = new QLabel("? item(s)");
    m_infocount->setAlignment(Qt::AlignRight);
    m_infocount->setMargin(8);
    m_infocount->setStyleSheet( /*"background:#f5f5f5;"*/
                               "border-top:1px solid #e0e0e0;"
                               /*"border-bottom:1px solid #e0e0e0;"*/);


    root->addWidget(searchBar);
    root->addWidget(m_scrollArea, 1);
    root->addWidget(m_infocount);
}

// ── Veri yönetimi ─────────────────────────────────────────────

void CardListWidget::addCard(const CardItem &item)
{
    m_allItems.append(item);
    rebuildList(m_searchEdit->text());
}

void CardListWidget::addCards(const QList<CardItem> &items)
{
    m_allItems.append(items);
    rebuildList(m_searchEdit->text());
}

void CardListWidget::clearCards()
{
    m_allItems.clear();
    rebuildList();
}

// ── Filtre ─────────────────────────────────────────────────────

void CardListWidget::onSearchChanged(const QString &text)
{
    rebuildList(text);
}

void CardListWidget::rebuildList(const QString &filter)
{
    // Mevcut widget'ları temizle
    for (CardWidget *w : std::as_const(m_cardWidgets)) {
        m_listLayout->removeWidget(w);
        w->deleteLater();
    }
    m_cardWidgets.clear();

    // Stretch'i geçici kaldır
    QLayoutItem *stretch = m_listLayout->takeAt(m_listLayout->count() - 1);

    const QString f = filter.trimmed().toLower();

    for (const CardItem &item : std::as_const(m_allItems)) {
        // Filtre: ad veya yorum içinde geçiyor mu?
        if (!f.isEmpty()) {
            const bool inName    = item.name.toLower().contains(f);
            const bool inComment = item.comment.toLower().contains(f);
            const bool inDetail  = item.detail.toLower().contains(f);
            if (!inName && !inComment && !inDetail)
                continue;
        }

        auto *card = new CardWidget(item, m_container);
        connect(card, &CardWidget::clicked,
                this, &CardListWidget::cardClicked);

        m_cardWidgets.append(card);
        m_listLayout->addWidget(card);
    }

    // Stretch'i geri ekle
    m_listLayout->addItem(stretch);

    // Boş durum etiketi
    // (varsa öncekini sil)
    if (QWidget *old = m_container->findChild<QLabel*>("emptyLabel"))
        old->deleteLater();

    if (m_cardWidgets.isEmpty()) {
        auto *empty = new QLabel("No items found", m_container);
        empty->setObjectName("emptyLabel");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color:#9e9e9e; font-size:14px; padding:24px;");
        m_listLayout->insertWidget(0, empty);
    }

    // Filtre veya değil item sayısı
    int itemcount = m_cardWidgets.count();
    if (itemcount == 0)
        m_infocount->setText("No modules found");
    else
        m_infocount->setText(QString::number(itemcount) + " module" + ((itemcount>1)?"s":""));
}
