#include "cardwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QFont>
/*
// ── Yardımcı: resmi yuvarlak köşeli kare thumbnail'e dönüştür ──
static QPixmap makeRoundedThumb(const QPixmap &src, int w, int h, int radius)
{
    QPixmap scaled = src.scaled(w, h,
                                Qt::KeepAspectRatioByExpanding,
                                Qt::SmoothTransformation);

    // Ortayı kırp
    if (scaled.width() > w || scaled.height() > h) {
        const int x = (scaled.width()  - w) / 2;
        const int y = 0; //(scaled.height() - h) / 2;
        scaled = scaled.copy(x, y, w, h);
    }

    QPixmap result(w, h);
    result.fill(Qt::transparent);

    QPainter p(&result);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(0, 0, w, h, radius, radius);
    p.setClipPath(path);
    p.drawPixmap(0, 0, scaled);
    return result;
}

// ── Yardımcı: baş harf placeholder pixmap ──
static QPixmap makeInitialsPixmap(const QString &name, int w, int h)
{
    // İlk iki kelimenin baş harfleri
    QStringList parts = name.split(' ', Qt::SkipEmptyParts);
    QString initials;
    if (parts.size() >= 2)
        initials = initials = QString(parts[0][0].toUpper()) + QString(parts[1][0].toUpper());
    else if (!name.isEmpty())
        initials = name.left(2).toUpper();
    else
        initials = "??";

    QPixmap pix(w, h);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    // Yuvarlak köşeli arka plan
    p.setBrush(QColor(0xe8, 0xea, 0xf6));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(0, 0, w, h, 6, 6);

    // Baş harfler
    QFont font;
    font.setPixelSize(w / 3);
    font.setBold(true);
    p.setFont(font);
    p.setPen(QColor(0x5c, 0x6b, 0xc0));
    p.drawText(QRect(0, 0, w, h), Qt::AlignCenter, initials);

    return pix;
}
*/
// ────────────────────────────────────────────────────────────────

CardWidget::CardWidget(const CardItem &item, QWidget *parent)
    : QWidget(parent)
    , m_item(item)
{
    setupUi();
    setMouseTracking(true);
    setCursor(Qt::PointingHandCursor);
    setMinimumHeight(82);
    setMaximumHeight(82);
}

void CardWidget::setupUi()
{
    constexpr int THUMBWIDTH = 85;
    constexpr int THUMBHEIGHT = 64;

    auto *root = new QHBoxLayout(this);
    root->setContentsMargins(12, 10, 12, 10);
    root->setSpacing(14);

    // ── Thumbnail ──────────────────────────────────────────────
    /*
    m_thumbLabel = new QLabel(this);
    m_thumbLabel->setFixedSize(THUMBWIDTH, THUMBHEIGHT);

    QPixmap px(m_item.imagePath);
    if (px.isNull())
        px = makeInitialsPixmap(m_item.name, THUMBWIDTH, THUMBHEIGHT);
    else
        px = makeRoundedThumb(px, THUMBWIDTH, THUMBHEIGHT, 6);

    m_thumbLabel->setPixmap(px);
    m_thumbLabel->setAlignment(Qt::AlignCenter);
    */

    m_thumbLabel = new GifWidget(m_item.imagePath, this);
    m_thumbLabel->setFixedSize(THUMBWIDTH, THUMBHEIGHT);
    m_thumbLabel->setScaledContents(true);

    // ── Metin alanı ────────────────────────────────────────────
    auto *textCol = new QVBoxLayout;
    textCol->setSpacing(4);
    textCol->setContentsMargins(0, 0, 0, 0);

    // Ad
    m_nameLabel = new QLabel(m_item.name, this);
    QFont nameFont = m_nameLabel->font();
    nameFont.setPixelSize(14);
    nameFont.setWeight(QFont::Weight::DemiBold);
    m_nameLabel->setFont(nameFont);
    m_nameLabel->setStyleSheet("background-color: transparent; color: #212121;");

    // Yorum — maksimum 64 karakter + "…"
    const QString shortComment = m_item.comment.length() > 64
        ? m_item.comment.left(64) + QChar(0x2026)   // …
        : m_item.comment;

    m_commentLabel = new QLabel(shortComment, this);
    QFont commentFont = m_commentLabel->font();
    commentFont.setPixelSize(12);
    m_commentLabel->setFont(commentFont);
    m_commentLabel->setStyleSheet("background-color: transparent; color: #757575;");
    m_commentLabel->setWordWrap(false);

    QString statusText("FREE");
    QString statusColor("green");
    switch (m_item.accessType) {
        case CardItem::AccessType::Locked:
            statusText="LOCKED"; statusColor = "red"; break;
        case CardItem::AccessType::Unlocked:
            statusText="UNLOCKED"; break;
        //case CardItem::AccessType::Free: statusText="FREE"; break;
        default:
        break;
    }

    m_statusLabel = new QLabel(statusText, this);
    QFont statusFont = m_statusLabel->font();
    statusFont.setBold(true);
    statusFont.setPixelSize(9);
    m_statusLabel->setAlignment(Qt::AlignRight);
    m_statusLabel->setFont(statusFont);
    statusColor = QString("background-color: transparent; color:"+statusColor+";");
    m_statusLabel->setStyleSheet(statusColor);
    m_statusLabel->setWordWrap(false);

    textCol->addStretch();
    textCol->addWidget(m_statusLabel);
    textCol->addWidget(m_nameLabel);
    textCol->addWidget(m_commentLabel);
    textCol->addStretch();

    // ── Sağ ok ─────────────────────────────────────────────────
    auto *arrowLabel = new QLabel("›", this);
    QFont arrowFont = arrowLabel->font();
    arrowFont.setPixelSize(22);
    arrowLabel->setFont(arrowFont);
    arrowLabel->setStyleSheet("background-color: transparent; color: #bdbdbd;");
    arrowLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    root->addWidget(m_thumbLabel);
    root->addLayout(textCol, 1);
    root->addWidget(arrowLabel);
}

// ── Hover & click ──────────────────────────────────────────────

void CardWidget::setHovered(bool hovered)
{
    m_hovered = hovered;
    update();   // paintEvent'i tetikle
}

void CardWidget::enterEvent(QEnterEvent *event)
{
    setHovered(true);
    QWidget::enterEvent(event);
}

void CardWidget::leaveEvent(QEvent *event)
{
    setHovered(false);
    QWidget::leaveEvent(event);
}

void CardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(m_item);
    QWidget::mousePressEvent(event);
}

// ── Arka plan çizimi (border + hover rengi) ────────────────────

void CardWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const QColor bg     = m_hovered ? QColor(0xf0, 0xf4, 0xff) : QColor(0xff, 0xff, 0xff);
    const QColor border = m_hovered ? QColor(0xc5, 0xca, 0xe9) : QColor(0xe0, 0xe0, 0xe0);

    p.setPen(QPen(border, 1));
    p.setBrush(bg);
    p.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 6, 6);
}
