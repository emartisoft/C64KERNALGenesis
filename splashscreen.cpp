#include "splashscreen.h"


SplashScreen::SplashScreen(const QPixmap &pixmap, QWidget *parent)
    : QWidget(parent), m_pixmap(pixmap)
{
    // Çerçeve ve görev çubuğu girişini kaldır
    setWindowFlags(Qt::Window
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::Tool);              // Task bar'da görünmez

    // Alfa kanalı (şeffaflık) için zorunlu
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    resize(m_pixmap.size());

    // Ekran ortasına konumlandır
    QRect screen = QGuiApplication::primaryScreen()->geometry();
    move((screen.width()  - width())  / 2,
         (screen.height() - height()) / 2);
}

void SplashScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // Smooth scaling & alfa desteği
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0, 0, m_pixmap);
}
