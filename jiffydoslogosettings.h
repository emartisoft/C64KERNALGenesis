#ifndef JIFFYDOSLOGOSETTINGS_H
#define JIFFYDOSLOGOSETTINGS_H

#include <QDialog>

namespace Ui {
class JiffyDOSLogoSettings;
}

class JiffyDOSLogoSettings : public QDialog
{
    Q_OBJECT

public:
    explicit JiffyDOSLogoSettings(QWidget *parent = nullptr);
    ~JiffyDOSLogoSettings();

    QString yourText() const { return m_yourText; }
    bool    c64Text() const { return m_c64text; }
    int    rightTextIndex() const { return m_rightTextIndex; }
    bool    noblink() const { return m_noblink; }

private slots:
    void on_okBtn_clicked();

    void on_bDefault_clicked();

    void on_rV601_clicked(bool checked);

    void on_rYourText_clicked(bool checked);

    void on_rNone_clicked(bool checked);

    void on_cC64Text_clicked(bool checked);

    void on_lYourText_textChanged(const QString &arg1);

    void on_cNoBlink_clicked(bool checked);

private:
    Ui::JiffyDOSLogoSettings *ui;

    QString m_yourText;
    bool m_c64text;
    int m_rightTextIndex;
    bool    m_noblink;
};

#endif // JIFFYDOSLOGOSETTINGS_H
