#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>
#include <QPixmap>
#include <QScreen>
#include <QPainter>
#include <QWidget>

class SplashScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SplashScreen(const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QPixmap m_pixmap;
};

#endif // SPLASHSCREEN_H
