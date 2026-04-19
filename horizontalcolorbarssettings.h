#ifndef HORIZONTALCOLORBARSSETTINGS_H
#define HORIZONTALCOLORBARSSETTINGS_H

#include <QDialog>

namespace Ui {
class horizontalcolorbarssettings;
}

class horizontalcolorbarssettings : public QDialog
{
    Q_OBJECT

public:
    explicit horizontalcolorbarssettings(QWidget *parent = nullptr);
    ~horizontalcolorbarssettings();
    void setScreenColors(QColor border, QColor background, QColor text);
    int     topLineColorIndex()  const { return m_topColor; }
    int     bottomLineColorIndex()  const { return m_bottomColor;}
    int     centerLineColorIndex()  const { return m_centerColor;}


private slots:
    void on_bOK_clicked();

    void on_cCenterLine_currentIndexChanged(int index);

    void on_cTopLine_currentIndexChanged(int index);

    void on_cBottomLine_currentIndexChanged(int index);

private:
    Ui::horizontalcolorbarssettings *ui;
    void setColorsForImage();
    QColor m_border, m_background, m_text;
    int m_topColor, m_bottomColor, m_centerColor;
};

#endif // HORIZONTALCOLORBARSSETTINGS_H
