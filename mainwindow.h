#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlistwidget.h>
#include "carditem.h"
#include "BouncingSprite.h"
#include "advancedsettingsdialog.h"
#include "jiffydoslogosettings.h"
#include "commodorelogosettings.h"
#include "commodore64logosettings.h"
#include "ultimatesettings.h"
#include "commodoretextsettings.h"
#include "horizontalcolorbarssettings.h"
#include "about.h"

class CardListWidget;
class DetailPage;
class QStackedWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openRomButton_clicked();

    void on_saveRomButton_clicked();

    void on_actionAbout_Qt_triggered();

    void onCardClicked(const CardItem &item);

    void onBackRequested();

    void onApplyRequested();

    void onAdvancedSettingsRequested();

    void onUnlockRequested();

    void onWhyunlockRequested();

    void on_bDefaultColors_clicked();

    void on_bPatch_clicked();

    void on_info1_linkActivated(const QString &link);

    void on_bBack_clicked();

    void on_actionExit_triggered();

    void on_actionRewrite_the_Moment_of_Power_triggered();

    void on_action_getroms_triggered();

    void on_actionSettings_triggered();

    void on_bSaveSettings_clicked();

    void on_bEmulatorPath_clicked();

    void on_bTestRomFile_clicked();

    void on_actionLoad_a_module_triggered();

    void on_actionC_Balloon_Sprite_toggled(bool checked);

    void on_label_10_linkActivated(const QString &link);

    void on_bChargenPath_clicked();

    void on_actionAbout_triggered();

    void on_actionModule_Store_triggered();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    CardListWidget  *m_listWidget  = nullptr;
    DetailPage      *m_detailPage  = nullptr;
    int dBorder, dBackground, dText;
    QString selectedModuleName;
    int selectedModuleIndex;
    QByteArray baDir, baName;
    BouncingSprite* m_sprite = nullptr;
    AdvancedSettingsDialog *dialog = nullptr;
    JiffyDOSLogoSettings *jiffydoslogoSettings = nullptr;
    CommodoreLogoSettings *commodorelogoSettings = nullptr;
    CommodoreLogo64Settings *commodore64logoSettings = nullptr;
    UltimateSettings *ultimatesettings = nullptr;
    CommodoreTextSettings *commodoreetextsettings = nullptr;
    horizontalcolorbarssettings *horizontalColorBarsSettings = nullptr;
    About *about = nullptr;


    QByteArray romData;
    bool romLoaded = false;
    void setScreenPreviewColors();
    void getKernalRomImage();
    void setDefaultColors();

    void loadItems();
    void setupRom(bool test=true);
    void launchApp(const QString &appPath, const QString &romPath, const QString &chargenPath="");

    void    extractZip(const QString &zipPath);
    void    copyM64(const QString &filePath);

    void onTimer();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
