#include "detailpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QFrame>

DetailPage::DetailPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void DetailPage::setupUi()
{
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    auto *toolbar = new QWidget(this);
    toolbar->setFixedHeight(48);
    toolbar->setStyleSheet("background:#909090;");

    auto *toolRow = new QHBoxLayout(toolbar);
    toolRow->setContentsMargins(8, 0, 8, 0);

    const QString buttonStyle =         "QPushButton {"
                                "  background: rgba(255,255,255,0.15);"
                                "  color: white;"
                                "  border: none;"
                                "  border-radius: 4px;"
                                "  padding: 8px 8px;"
                                "  font-size: 13px;"
                                "}"
                                "QPushButton:hover {"
                                "  background: rgba(255,255,255,0.25);"
                                "}"
                                "QPushButton:pressed {"
                                "  background: rgba(255,255,255,0.10);"
                                "}";

    auto *backBtn = new QPushButton("‹  Back", toolbar);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet(buttonStyle);
    connect(backBtn, &QPushButton::clicked, this, &DetailPage::backRequested);

    whyunlock = new QLabel("<html><head/><body><p><a href=\"whyunlock\"><span style=\" text-decoration: underline; color:white;\">Why unlock?</span></a></p></body></html>", toolbar);
    whyunlock->setCursor(Qt::PointingHandCursor);
    connect(whyunlock, &QLabel::linkActivated, this, &DetailPage::whyunlockRequested);

    unlockBtn = new QPushButton("Unlock", toolbar);
    unlockBtn->setCursor(Qt::PointingHandCursor);
    unlockBtn->setStyleSheet(buttonStyle);
    connect(unlockBtn, &QPushButton::clicked, this, &DetailPage::unlockRequested);

    advancedSettingsBtn = new QPushButton("Advanced Settings", toolbar);
    advancedSettingsBtn->setCursor(Qt::PointingHandCursor);
    advancedSettingsBtn->setStyleSheet(buttonStyle);
    connect(advancedSettingsBtn, &QPushButton::clicked, this, &DetailPage::advancedSettingsRequested);

    applyBtn = new QPushButton("Apply", toolbar);
    applyBtn->setCursor(Qt::PointingHandCursor);
    applyBtn->setStyleSheet(buttonStyle);
    connect(applyBtn, &QPushButton::clicked, this, &DetailPage::applyRequested);

    toolRow->addWidget(backBtn);
    toolRow->addStretch();
    toolRow->addWidget(whyunlock);
    toolRow->addWidget(unlockBtn);
    toolRow->addWidget(advancedSettingsBtn);
    toolRow->addWidget(applyBtn);

    // ── Kaydırılabilir içerik alanı ──────────────────────────
    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet(
        "QScrollBar:vertical { width:6px; background:transparent; }"
        "QScrollBar::handle:vertical { background:#c0c0c0; border-radius:3px; min-height:24px; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0; }"
    );

    auto *content = new QWidget;
    content->setStyleSheet("background:white;");
    auto *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);

    // Hero resim
    m_heroLabel = new GifWidget(content);
    m_heroLabel->setFixedHeight(272);
    m_heroLabel->setFixedWidth(360);
    m_heroLabel->setAlignment(Qt::AlignCenter);
    //m_heroLabel->setStyleSheet("background:#e8eaf6;");
    m_heroLabel->setScaledContents(true);

    // İçerik kartı
    auto *card = new QWidget(content);
    card->setStyleSheet("background:white;");
    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(24, 20, 24, 24);
    cardLayout->setSpacing(12);

    // Başlık
    m_nameLabel = new QLabel(card);
    QFont nameFont = m_nameLabel->font();
    nameFont.setPixelSize(20);
    nameFont.setWeight(QFont::Bold);
    m_nameLabel->setFont(nameFont);
    m_nameLabel->setStyleSheet("color:#212121;");
    m_nameLabel->setWordWrap(true);

    // Tam yorum satırı
    auto *commentRow = new QWidget(card);
    auto *commentRowLayout = new QHBoxLayout(commentRow);
    commentRowLayout->setContentsMargins(0,0,0,0);
    commentRowLayout->setSpacing(8);

    auto *bubbleIcon = new QLabel("", commentRow);
    bubbleIcon->setPixmap(QPixmap(":/res/pictures/bubble.png"));
    bubbleIcon->setScaledContents(true);
    bubbleIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_commentLabel = new QLabel(commentRow);
    QFont commentFont = m_commentLabel->font();
    commentFont.setPixelSize(13);
    commentFont.setItalic(true);
    m_commentLabel->setFont(commentFont);
    m_commentLabel->setStyleSheet("color:#5c6bc0;");
    m_commentLabel->setWordWrap(true);

    commentRowLayout->addWidget(bubbleIcon, 0, Qt::AlignTop);
    commentRowLayout->addWidget(m_commentLabel, 1);

    // Ayırıcı 2
    auto *sep2 = new QFrame(card);
    sep2->setFrameShape(QFrame::HLine);
    sep2->setStyleSheet("color:#eeeeee;");

    // Detay metni
    m_detailLabel = new QLabel(card);
    QFont detailFont = m_detailLabel->font();
    detailFont.setPixelSize(13);
    m_detailLabel->setFont(detailFont);
    m_detailLabel->setStyleSheet("color:#424242; line-height:1.6;");
    m_detailLabel->setWordWrap(true);
    m_detailLabel->setTextFormat(Qt::PlainText);
    m_detailLabel->setAlignment(Qt::AlignTop | Qt::AlignJustify);

    cardLayout->addWidget(m_nameLabel);
    //cardLayout->addWidget(sep1);
    cardLayout->addWidget(commentRow);
    cardLayout->addWidget(sep2);
    cardLayout->addWidget(m_detailLabel);
    cardLayout->addStretch();

    contentLayout->addSpacing(8);
    contentLayout->addWidget(m_heroLabel, 0, Qt::AlignCenter);
    contentLayout->addWidget(card, 1);

    scrollArea->setWidget(content);

    root->addWidget(toolbar);
    root->addWidget(scrollArea, 1);
}

void DetailPage::setCard(const CardItem &item)
{
    m_item = item;
    // Hero resim
    /*
    QPixmap px(item.imagePath);
    if (!px.isNull()) {
        m_heroLabel->setPixmap(px);
    } else {
        // Placeholder: baş harfler
        QPixmap ph(440, 200);
        ph.fill(QColor(0xe8, 0xea, 0xf6));
        QPainter p(&ph);
        QFont f; f.setPixelSize(64); f.setBold(true); p.setFont(f);
        p.setPen(QColor(0x9f, 0xa8, 0xda));
        p.drawText(ph.rect(), Qt::AlignCenter,
                   item.name.length() >= 2 ? item.name.left(2).toUpper() : "??");
        m_heroLabel->setPixmap(ph);
    }
    */
    m_heroLabel->setGif(item.imagePath);

    m_nameLabel->setText(item.name);
    m_commentLabel->setText(item.comment);   // detay sayfasında tam metin
    m_detailLabel->setText(item.detail);

    // unlock or apply
    if(m_item.accessType == CardItem::AccessType::Locked)
    {
        whyunlock->setVisible(true);
        unlockBtn->setVisible(true);
        applyBtn->setVisible(false);
    }
    else
    {
        whyunlock->setVisible(false);
        unlockBtn->setVisible(false);
        applyBtn->setVisible(true);
    }

    advancedSettingsBtn->setVisible(m_item.hasAdvancedSettings);

}
