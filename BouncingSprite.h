// BouncingSprite.h  --  PNG veya GIF destekli, sinüs eğrili hareket, Qt6 C++17
#pragma once

#include <QLabel>
#include <QTimer>
#include <QMovie>

class BouncingSprite : public QLabel
{
    Q_OBJECT

public:
    explicit BouncingSprite(const QString& resourcePath,
                            QWidget*       parent,
                            int            intervalMs = 16);

    ~BouncingSprite();

    void start();
    void stop();

    void setSpeed(double speed)        { m_speed = speed; }
    void setWaveAmplitude(double amp)  { m_waveAmp = amp; }
    void setWaveFrequency(double freq) { m_waveFreq = freq; }

    // Orijinal en/boy oranını koruyarak ölçekle.
    // setSize(64, 64) → en fazla 64x64 içine sığdır
    // setSize(0, 48)  → yüksekliği 48 yap, genişliği oran ile hesapla
    // setSize(96, 0)  → genişliği 96 yap, yüksekliği oran ile hesapla
    void setSize(int w, int h);

private slots:
    void onTick();
    void onFrameChanged(int frame);   // GIF boyutu değişirse pozisyonu güncelle

private:
    void loadResource(const QString& path);

    QTimer  m_timer;
    QMovie* m_movie = nullptr;   // GIF için, PNG'de nullptr

    double m_angle    = 0.785;
    double m_speed    = 3.0;
    double m_waveAmp  = 0.04;
    double m_waveFreq = 0.05;
    double m_waveT    = 0.0;
    double m_x        = 0.0;
    double m_y        = 0.0;
    QSize  m_originalSize;   // orijinal görsel boyutu
};
