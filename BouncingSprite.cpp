// BouncingSprite.cpp  --  PNG veya GIF destekli, sinüs eğrili hareket, Qt6 C++17
#include "BouncingSprite.h"

#include <QWidget>
#include <QPixmap>
#include <QFileInfo>
#include <cmath>

BouncingSprite::BouncingSprite(const QString& resourcePath,
                               QWidget*       parent,
                               int            intervalMs)
    : QLabel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAlignment(Qt::AlignCenter);

    loadResource(resourcePath);

    // Başlangıç pozisyonu merkez
    if (parent) {
        m_x = (parent->width()  - width())  / 2.0;
        m_y = (parent->height() - height()) / 2.0;
        move(int(m_x), int(m_y));
    }

    connect(&m_timer, &QTimer::timeout, this, &BouncingSprite::onTick);
    m_timer.setInterval(intervalMs);
}

BouncingSprite::~BouncingSprite()
{
    // m_movie parent'a bağlı, Qt otomatik siler
}

void BouncingSprite::loadResource(const QString& path)
{
    // Uzantıya göre GIF mi PNG mi karar ver
    QString ext = QFileInfo(path).suffix().toLower();

    if (ext == "gif") {
        m_movie = new QMovie(path, QByteArray(), this);

        if (m_movie->isValid()) {
            setMovie(m_movie);
            m_movie->jumpToFrame(0);          // ilk kareye git, boyutu al
            m_originalSize = m_movie->currentPixmap().size();
            resize(m_originalSize);

            // Kare değişince boyut farklılaşırsa güncelle
            connect(m_movie, &QMovie::frameChanged,
                    this,    &BouncingSprite::onFrameChanged);
        } else {
            delete m_movie;
            m_movie = nullptr;
        }
    } else {
        // PNG veya diğer statik görsel
        QPixmap pm(path);
        if (!pm.isNull()) {
            m_originalSize = pm.size();
            setPixmap(pm);
            resize(m_originalSize);
        }
    }
}

void BouncingSprite::setSize(int w, int h)
{
    if (m_originalSize.isEmpty()) return;

    QSize target;
    if (w > 0 && h > 0) {
        // Her ikisi verilmiş — oranı koruyarak sığdır
        target = m_originalSize.scaled(w, h, Qt::KeepAspectRatio);
    } else if (w > 0) {
        // Sadece genişlik — yüksekliği oran ile hesapla
        double ratio = double(m_originalSize.height()) / double(m_originalSize.width());
        target = QSize(w, int(w * ratio));
    } else if (h > 0) {
        // Sadece yükseklik — genişliği oran ile hesapla
        double ratio = double(m_originalSize.width()) / double(m_originalSize.height());
        target = QSize(int(h * ratio), h);
    } else {
        return;
    }

    resize(target);
    setScaledContents(true);   // QLabel içeriği widget boyutuna ölçekler

    // GIF için mevcut kareyi de ölçekle
    if (m_movie)
        m_movie->setScaledSize(target);
}

void BouncingSprite::onFrameChanged(int /*frame*/)
{
    // GIF karesi değişince boyut değişmişse widget'ı güncelle
    if (m_movie) {
        QSize s = m_movie->currentPixmap().size();
        if (s != size()) resize(s);
    }
}

void BouncingSprite::start()
{
    show();
    raise();
    if (m_movie) m_movie->start();   // GIF animasyonunu başlat
    m_timer.start();                  // hareket timer'ını başlat
}

void BouncingSprite::stop()
{
    m_timer.stop();
    if (m_movie) m_movie->stop();
    hide();
}

void BouncingSprite::onTick()
{
    QWidget* p = parentWidget();
    if (!p) return;

    const int pw = p->width();
    const int ph = p->height();
    const int sw = width();
    const int sh = height();

    // Sinüs dalgası açıyı modüle eder
    m_waveT += m_waveFreq;
    double effectiveAngle = m_angle + m_waveAmp * std::sin(m_waveT);

    double nx = m_x + m_speed * std::cos(effectiveAngle);
    double ny = m_y + m_speed * std::sin(effectiveAngle);

    // Yatay sınır
    if (nx <= 0.0) {
        nx = 0.0;
        m_angle = M_PI - m_angle;
        m_waveT = 0.0;
    } else if (nx + sw >= pw) {
        nx = double(pw - sw);
        m_angle = M_PI - m_angle;
        m_waveT = 0.0;
    }

    // Dikey sınır
    if (ny <= 0.0) {
        ny = 0.0;
        m_angle = -m_angle;
        m_waveT = 0.0;
    } else if (ny + sh >= ph) {
        ny = double(ph - sh);
        m_angle = -m_angle;
        m_waveT = 0.0;
    }

    // Açıyı [-π, π] aralığında tut
    while (m_angle >  M_PI) m_angle -= 2.0 * M_PI;
    while (m_angle < -M_PI) m_angle += 2.0 * M_PI;

    m_x = nx;
    m_y = ny;
    move(int(m_x), int(m_y));
    raise();
}
