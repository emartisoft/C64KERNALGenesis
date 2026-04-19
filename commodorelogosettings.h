#ifndef COMMODORELOGOSETTINGS_H
#define COMMODORELOGOSETTINGS_H

#include <QDialog>
#include <QColor>

namespace Ui {
class CommodoreLogoSettings;
}

class CommodoreLogoSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CommodoreLogoSettings(QWidget *parent = nullptr);
    ~CommodoreLogoSettings();
    void setScreenColors(QColor border, QColor background, QColor text);

    int     majorColorIndex()  const { return m_major; }
    int     minorColorIndex()  const { return m_minor; }
    QString topLine() const { return m_topline;}
    QString bottomLine() const { return m_bottomline;}
    int     topColorIndex()  const { return m_topColor; }
    int     bottomColorIndex()  const { return m_bottomColor; }

private slots:

    void on_bOK_clicked();

    void on_lTopline_textChanged(const QString &arg1);

    void on_lBottomLine_textChanged(const QString &arg1);

    void on_cTopLine_currentIndexChanged(int index);

    void on_cBottomLine_currentIndexChanged(int index);

private:
    Ui::CommodoreLogoSettings *ui;
    void setColorsForImage();
    QColor m_border, m_background, m_text;
    int m_major, m_minor, m_topColor, m_bottomColor;
    QString m_topline, m_bottomline;
};

#endif // COMMODORELOGOSETTINGS_H
