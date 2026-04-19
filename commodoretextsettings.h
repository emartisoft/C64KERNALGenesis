#ifndef COMMODORETEXTSETTINGS_H
#define COMMODORETEXTSETTINGS_H

#include <QDialog>

namespace Ui {
class CommodoreTextSettings;
}

class CommodoreTextSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CommodoreTextSettings(QWidget *parent = nullptr);
    ~CommodoreTextSettings();
    void setScreenColors(QColor border, QColor background, QColor text);
    int     topLineColorIndex()  const { return m_topColor; }
    int     bottomLineColorIndex()  const { return m_bottomColor;}

private slots:
    void on_bOK_clicked();

    void on_cTopLine_currentIndexChanged(int index);

    void on_cBottomLine_currentIndexChanged(int index);

private:
    Ui::CommodoreTextSettings *ui;
    void setColorsForImage();
    QColor m_border, m_background, m_text;
    int m_topColor, m_bottomColor;
};

#endif // COMMODORETEXTSETTINGS_H
