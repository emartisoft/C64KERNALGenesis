#ifndef CHANGECOLOR_H
#define CHANGECOLOR_H

/*
ColorReplacer cr(originalImage);

// Tek renk
cr.replaceColor(Qt::red, Qt::blue);

// Zincirleme
cr.replaceColor(QColor(255,0,0), QColor(0,0,255))
  .replaceColor(QColor(0,255,0), QColor(255,255,0));

// Swap - güvenli
cr.replaceColors({
    { Qt::red,  Qt::blue },
    { Qt::blue, Qt::red  }
});

// Tolerance ile (JPEG veya fotoğraf gibi durumlarda)
cr.replaceColor(Qt::red, Qt::blue, 20);

// Sonucu al
QImage result = cr.image();
*/

#include <QImage>
#include <QColor>
#include <QList>

class ColorReplacer
{
public:
    explicit ColorReplacer(const QImage& image)
        : m_image(image.convertToFormat(QImage::Format_ARGB32))
    {}

    void setImage(const QImage& image)
    {
        m_image = image.convertToFormat(QImage::Format_ARGB32);
    }

    QImage image() const
    {
        return m_image;
    }

    // Tek renk değiştirme (tolerance opsiyonel)
    ColorReplacer& replaceColor(const QColor& targetColor,
                                const QColor& newColor,
                                int tolerance = 0)
    {
        for (int y = 0; y < m_image.height(); ++y)
        {
            QRgb* line = reinterpret_cast<QRgb*>(m_image.scanLine(y));
            for (int x = 0; x < m_image.width(); ++x)
            {
                const QColor current = QColor::fromRgba(line[x]);
                if (isCloseColor(current, targetColor, tolerance))
                {
                    const int alpha = line[x] >> 24;
                    line[x] = (alpha << 24) | (newColor.rgb() & 0x00FFFFFF);
                }
            }
        }
        return *this;
    }

    // Çoklu renk değiştirme - swap güvenli (tek geçiş)
    ColorReplacer& replaceColors(const QList<QPair<QColor, QColor>>& colorMap,
                                 int tolerance = 0)
    {
        for (int y = 0; y < m_image.height(); ++y)
        {
            QRgb* line = reinterpret_cast<QRgb*>(m_image.scanLine(y));
            for (int x = 0; x < m_image.width(); ++x)
            {
                const QColor current = QColor::fromRgba(line[x]);
                for (auto& [target, replacement] : colorMap)
                {
                    if (isCloseColor(current, target, tolerance))
                    {
                        const int alpha = line[x] >> 24;
                        line[x] = (alpha << 24) | (replacement.rgb() & 0x00FFFFFF);
                        break; // ilk eşleşen kural uygulanır
                    }
                }
            }
        }
        return *this;
    }

private:
    QImage m_image;

    static bool isCloseColor(const QColor& c1, const QColor& c2, int tolerance)
    {
        if (tolerance == 0)
            return c1.rgb() == c2.rgb();

        return std::abs(c1.red()   - c2.red())   <= tolerance &&
               std::abs(c1.green() - c2.green()) <= tolerance &&
               std::abs(c1.blue()  - c2.blue())  <= tolerance;
    }
};

#endif // CHANGECOLOR_H