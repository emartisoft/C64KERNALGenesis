#ifndef ULTIMATESETTINGS_H
#define ULTIMATESETTINGS_H

#include <QDialog>

namespace Ui {
class UltimateSettings;
}

class UltimateSettings : public QDialog
{
    Q_OBJECT

public:
    explicit UltimateSettings(QWidget *parent = nullptr);
    ~UltimateSettings();

    void setScreenColors(QColor border, QColor background, QColor text);

    int     majorColorIndex()  const { return m_major; }
    int     minorColorIndex()  const { return m_minor; }
    int     topColorIndex()  const { return m_top; }
    int     bottomColorIndex()  const { return m_bottom; }
    QString topLine() const { return m_topline;}
    QString bottomLine() const { return m_bottomline;}
    int     topLineColorIndex()  const { return m_topColor; }
    int     bottomLineColorIndex()  const { return m_bottomColor;}

private slots:
    void on_bOK_clicked();

    void on_cTopLine_currentIndexChanged(int index);

    void on_cBottomLine_currentIndexChanged(int index);

    void on_lTopline_textChanged(const QString &arg1);

    void on_lBottomLine_textChanged(const QString &arg1);

private:
    Ui::UltimateSettings *ui;
    void setColorsForImage();
    QColor m_border, m_background, m_text;
    int m_major, m_minor, m_top, m_bottom, m_topColor, m_bottomColor;
    QString m_topline, m_bottomline;
};

#endif // ULTIMATESETTINGS_H
