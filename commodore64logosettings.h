#ifndef COMMODORE64LOGOSETTINGS_H
#define COMMODORE64LOGOSETTINGS_H

#include <QDialog>
#include <QColor>

namespace Ui {
class CommodoreLogo64Settings;
}

class CommodoreLogo64Settings : public QDialog
{
    Q_OBJECT

public:
    explicit CommodoreLogo64Settings(QWidget *parent = nullptr);
    ~CommodoreLogo64Settings();
    void setScreenColors(QColor border, QColor background, QColor text);

    int     majorColorIndex()  const { return m_major; }
    int     minorColorIndex()  const { return m_minor; }
    QString topLine() const { return m_topline;}
    QString bottomLine() const { return m_bottomline;}
    int     topColorIndex()  const { return m_topColor; }
    int     bottomColorIndex()  const { return m_bottomColor; }
    int     top64ColorIndex()  const { return m_top64Color; }
    int     bottom64ColorIndex()  const { return m_bottom64Color; }

private slots:

    void on_bOK_clicked();

    void on_lTopline_textChanged(const QString &arg1);

    void on_lBottomLine_textChanged(const QString &arg1);

    void on_cTopLine_currentIndexChanged(int index);

    void on_cBottomLine_currentIndexChanged(int index);

private:
    Ui::CommodoreLogo64Settings *ui;
    void setColorsForImage();
    QColor m_border, m_background, m_text;
    int m_major, m_minor, m_topColor, m_bottomColor, m_top64Color, m_bottom64Color;
    QString m_topline, m_bottomline;
};

#endif // COMMODORE64LOGOSETTINGS_H
