#ifndef ADVANCEDSETTINGSDIALOG_H
#define ADVANCEDSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class AdvancedSettingsDialog;
}

class AdvancedSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedSettingsDialog(QWidget *parent = nullptr);
    ~AdvancedSettingsDialog();

    // Getters
    QString yourText() const { return m_yourText; }
    int     cursorColorIndex()  const { return m_cursorColorIndex; }
    int     bootTextIndex() const { return m_boottextindex; }
    bool    noblink() const { return m_noblink; }
    bool    beep() const { return m_beep; }
    bool    hasCursorColor() const { return m_hasCursorColor; }

private slots:
    void on_pushButton_clicked();

    void on_cBeep_clicked(bool checked);

    void on_cNoBlink_clicked(bool checked);

    void on_gBootText_clicked(bool checked);

    void on_lYourText_textChanged(const QString &arg1);

    void on_cursorColor_currentIndexChanged(int index);

    void on_bDefault_clicked();

    void on_rReady_clicked(bool checked);

    void on_rOk_clicked(bool checked);

    void on_gCursorColor_clicked(bool checked);

private:
    Ui::AdvancedSettingsDialog *ui;

    QString m_yourText;
    int     m_cursorColorIndex;
    int     m_boottextindex;
    bool    m_noblink;
    bool    m_beep;
    bool    m_hasCursorColor;
};

#endif // ADVANCEDSETTINGSDIALOG_H
