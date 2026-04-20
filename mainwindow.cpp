#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <QScreen>
#include <QDesktopServices>
#include <QSettings>
#include <QStyleFactory>
#include <QProcess>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "cardlistwidget.h"
#include "detailpage.h"
#include "patch/include/patch.h"
#include "modules.h"
#include "paths.h"
#include "gen_license/include/license_check.h"
#include "changecolor.h"

QSettings settings(appConfigDir()+"/settings.ini", QSettings::IniFormat);
static RomView view{ nullptr, 0 };

const QString nojiffydos("The ROM file cannot be JiffyDOS for this patch to be applied.");
const QString invalidrom("Invalid ROM File");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //settings
    bool checkedBalloon = settings.value("Balloon", true).toBool();
    int fwidth = settings.value("Width", 603).toInt();
    int fheight = settings.value("Height", 736).toInt();

    ui->setupUi(this);
    setAcceptDrops(true);

    // Formu önceki açıldığı size ile aç
    resize(fwidth, fheight);
    // Formu ortala
    QScreen *screen = QGuiApplication::screenAt(QCursor::pos());
    if (!screen) screen = QGuiApplication::primaryScreen();
    move(screen->geometry().center() - frameGeometry().center());

    ui->mainStackedWidget->setCurrentIndex(0);

    // border, background and text color combobox
    ui->backgroundColor->setCurrentIndex(0x06);
    ui->textColor->setCurrentIndex(0x0e);
    ui->borderColor->setCurrentIndex(0x0e);

    connect(ui->textColor, &QComboBox::currentIndexChanged, this, [=]() {
        setScreenPreviewColors();
    });

    connect(ui->backgroundColor, &QComboBox::currentIndexChanged, this, [=]() {
        setScreenPreviewColors();
    });

    connect(ui->borderColor, &QComboBox::currentIndexChanged, this, [=]() {
        setScreenPreviewColors();
    });

    setScreenPreviewColors();

    // Sayfa 0 — Liste
    m_listWidget = new CardListWidget(ui->stackedWidget);
    connect(m_listWidget, &CardListWidget::cardClicked,
            this, &MainWindow::onCardClicked);

    // Sayfa 1 — Detay
    m_detailPage = new DetailPage(ui->stackedWidget);
    connect(m_detailPage, &DetailPage::backRequested,
            this, &MainWindow::onBackRequested);
    connect(m_detailPage, &DetailPage::applyRequested,
            this, &MainWindow::onApplyRequested);
    connect(m_detailPage, &DetailPage::unlockRequested,
            this, &MainWindow::onUnlockRequested);
    connect(m_detailPage, &DetailPage::whyunlockRequested,
            this, &MainWindow::onWhyunlockRequested);
    connect(m_detailPage, &DetailPage::advancedSettingsRequested,
            this, &MainWindow::onAdvancedSettingsRequested);

    ui->stackedWidget->addWidget(m_listWidget);   // index 0
    ui->stackedWidget->addWidget(m_detailPage);   // index 1
    ui->stackedWidget->setCurrentIndex(0);

    ui->gifwidget1->setGif(":/res/pictures/genesis.gif");
    ui->info1->setOpenExternalLinks(false);
    ui->bBack->setVisible(false);

    // Balloon Sprite
    m_sprite = new BouncingSprite(":/res/pictures/balon.png", this, 16);
    m_sprite->setSize(32, 0);   // genişliği 96 yap, yükseklik otomatik
    m_sprite->setSpeed(1.0);          // hız — piksel/adım
    m_sprite->setWaveAmplitude(0.54); // eğri şiddeti — büyütünce daha belirgin viraj
    m_sprite->setWaveFrequency(0.15); // viraj sıklığı — büyütünce daha sık kıvrılır
    m_sprite->start(); 

    ui->EmulatorPath->setText(settings.value("EmulatorPath", "x64sc").toString());
    ui->ChargenPath->setText(settings.value("ChargenPath", "").toString());
    ui->actionC_Balloon_Sprite->setChecked(checkedBalloon);

    // defaults
    QString mp(modulesPath());
    baDir  = mp.toUtf8();
    selectedModuleIndex = 1;
    selectedModuleName = "just_colors";
    baName = selectedModuleName.toUtf8();

    loadItems();

    if (!dialog)
        dialog = new AdvancedSettingsDialog(this);
    if (!jiffydoslogoSettings)
        jiffydoslogoSettings = new JiffyDOSLogoSettings(this);
    if (!commodorelogoSettings)
        commodorelogoSettings = new CommodoreLogoSettings(this);
    if (!commodore64logoSettings)
        commodore64logoSettings = new CommodoreLogo64Settings(this);
    if (!ultimatesettings)
        ultimatesettings = new UltimateSettings(this);
    if (!commodoreetextsettings)
        commodoreetextsettings = new CommodoreTextSettings(this);
    if (!horizontalColorBarsSettings)
        horizontalColorBarsSettings = new horizontalcolorbarssettings(this);
    if (!about)
        about = new About(this);

    ui->lSettingsSaved->setVisible(false);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimer);
}

// Get the KERNAL revision from the ROM binary file that was opened
void MainWindow::getKernalRomImage()
{
    KernalRomImage rev = detectKernalRomImage(view);
    QString text = "C64 KERNAL\n";

    switch (rev) {
    case KernalRomImage::JiffyDOS: text.append("JiffyDOS"); break;
    case KernalRomImage::Rev1Prototype: text.append("REVISION 1 (PROTOTYPE)"); break;
    case KernalRomImage::Rev2Old: text.append("REVISION 2 (OLD)"); break;
    case KernalRomImage::Rev3New: text.append("REVISION 3 (NEW)"); break;
    case KernalRomImage::SX64: text.append("SX64"); break;
    case KernalRomImage::CreatedByThisApp: text.append("CREATED BY THIS APP"); break;
    default: text.append("UNKNOWN");
    }

    romLoaded = rev != KernalRomImage::Unknown;
    ui->kernalRomImage->setText(text);
    ui->lKernalTypeToProcess->setText("<html><head/><body><p><span style=\" font-weight:700;\">KERNAL Type to Process:</span> "+text+"</p></body></html>");
}

void MainWindow::setDefaultColors()
{
    ui->textColor->setCurrentIndex(dText);
    ui->borderColor->setCurrentIndex(dBorder);
    ui->backgroundColor->setCurrentIndex(dBackground);
    setScreenPreviewColors();
}

void MainWindow::loadItems()
{
    m_listWidget->clearCards();
    for (auto &item : items) {
        if (license_validate(baDir.constData(), item.moduleName.toUtf8().constData()))
            if(item.accessType == CardItem::AccessType::Locked)
                item.accessType = CardItem::AccessType::Unlocked;
    }
    m_listWidget->addCards(items);
}

void MainWindow::setupRom(bool test)
{
    if (!romLoaded) {
        QMessageBox::warning(this, "No ROM", "Load a valid ROM first.");
        return;
    }

    if(!license_validate(baDir.constData(), baName.constData()))
    {
        QMessageBox::critical(this, "Invalid License", "This module requires a valid license");
        return;
    }

    // QByteArray -> std::vector
    std::vector<uint8_t> romVec(
        reinterpret_cast<const uint8_t*>(romData.constData()),
        reinterpret_cast<const uint8_t*>(romData.constData()) + romData.size()
        );

    // Uygulama tarafından patch edildi imzası
    setCreatedByThisApp(romVec);

    // Renk bilgileri
    if(ui->textColor->currentIndex()==ui->backgroundColor->currentIndex()) QMessageBox::warning(this, "Color Conflict", "The text and background colors you have selected are the same value.");
    setTextBorderBackgroundColor(romVec, ui->textColor->currentIndex(), ui->borderColor->currentIndex(), ui->backgroundColor->currentIndex());

    // Modul Patch seçimi
    switch(selectedModuleIndex)
    {
        //------------------
        // Just Colors
        //case 0x001:

        //------------------
        // Just READY.
        case 0x002:
            setReady(romVec);
            break;

        //------------------
        // Just OK
        case 0x003:
            setOk(romVec);
            break;

        // Extended READY.
        case 0x004:
        {
            QString qYourText = dialog->yourText();
            unsigned char buf[25] = {};
            QByteArray bYourText = qYourText.toUtf8();
            memcpy(buf, bYourText.constData(), qMin((int)sizeof(buf), bYourText.size()));
            setExtendedReadyAdvancedSettings(romVec,
                                             buf,
                                             dialog->bootTextIndex(),
                                             dialog->hasCursorColor(),
                                             dialog->cursorColorIndex(),
                                             dialog->noblink(),
                                             dialog->beep()
                                             );
            break;
        }

        // Atari
        case 0x005:
        {
            setAtari(romVec);
            break;
        }

        // Fake RAM Test
        case 0x400:
        {
            setFakeRam(romVec);
            break;
        }

        // Commodore Logo
        case 0x500:
        {
            setCommodoreLogo(romVec, ui->textColor->currentIndex());
            break;
        }

        // Commodore Logo Enhanced
        case 0x580:
        {
            unsigned char bufTop[25] = {};
            unsigned char bufBottom[25] = {};
            QString topline, bottomline;
            topline = commodorelogoSettings->topLine();
            bottomline = commodorelogoSettings->bottomLine();

            if(topline.length()>0)
            {
                QByteArray bTopText = topline.toUtf8();
                memcpy(bufTop, bTopText.constData(), qMin((int)sizeof(bufTop), bTopText.size()));
            }
            else
                bufTop[0]=0x00;

            if(bottomline.length()>0)
            {
                QByteArray bBottomText = bottomline.toUtf8();
                memcpy(bufBottom, bBottomText.constData(), qMin((int)sizeof(bufBottom), bBottomText.size()));
            }
            else
                bufBottom[0]=0x00;

            setCommodoreLogoEnhanced(romVec,
                                     ui->textColor->currentIndex(),
                                     commodorelogoSettings->majorColorIndex(),
                                     commodorelogoSettings->minorColorIndex(),
                                     commodorelogoSettings->topColorIndex(),
                                     bufTop,
                                     commodorelogoSettings->bottomColorIndex(),
                                     bufBottom);
            break;
        }

        // Commodore 64 Logo Enhanced
        case 0x581:
        {
            unsigned char bufTop[25] = {};
            unsigned char bufBottom[25] = {};
            QString topline, bottomline;
            topline = commodore64logoSettings->topLine();
            bottomline = commodore64logoSettings->bottomLine();

            if(topline.length()>0)
            {
                QByteArray bTopText = topline.toUtf8();
                memcpy(bufTop, bTopText.constData(), qMin((int)sizeof(bufTop), bTopText.size()));
            }
            else
                bufTop[0]=0x00;

            if(bottomline.length()>0)
            {
                QByteArray bBottomText = bottomline.toUtf8();
                memcpy(bufBottom, bBottomText.constData(), qMin((int)sizeof(bufBottom), bBottomText.size()));
            }
            else
                bufBottom[0]=0x00;

            setCommodoreLogo64Enhanced(romVec,
                                     ui->textColor->currentIndex(),
                                     commodore64logoSettings->majorColorIndex(),
                                     commodore64logoSettings->minorColorIndex(),
                                     commodore64logoSettings->top64ColorIndex(),
                                     commodore64logoSettings->bottom64ColorIndex(),
                                     commodore64logoSettings->topColorIndex(),
                                     bufTop,
                                     commodore64logoSettings->bottomColorIndex(),
                                     bufBottom);
            break;
        }

        // Commodore Monochrome Logo
        case 0x510:
        {
            setCommodoreLogoMono(romVec);
            break;
        }

        // Commodore 64 Logo
        case 0x501:
        {
            setCommodoreLogo64(romVec, ui->textColor->currentIndex());
            break;
        }

        // Commodore 64 Monochrome Logo
        case 0x511:
        {
            setCommodoreLogo64Mono(romVec);
            break;
        }

        // IBM Style
        case 0x600:
        {
            setIBMStyle(romVec, ui->textColor->currentIndex());
            break;
        }

        // IBM Style
        case 0x700:
        {
            setC64RainbowBars(romVec, ui->textColor->currentIndex());
            break;
        }

        // Floppy Diskette Logo
        case 0x800:
        {
            setFloppyDiskette(romVec, ui->textColor->currentIndex());
            break;
        }

        // Horizontal Color Bars
        case 0x900:
        {
            setHorizontalColorBars(romVec, ui->textColor->currentIndex(), horizontalColorBarsSettings->topLineColorIndex(), horizontalColorBarsSettings->centerLineColorIndex(), horizontalColorBarsSettings->bottomLineColorIndex());
            break;
        }

        // Ultimate Monochrome
        case 0xa00:
        {
            setUltimateMono(romVec, ui->textColor->currentIndex());
            break;
        }

        // Ultimate
        case 0xa80:
        {
            switch (ui->backgroundColor->currentIndex()) {
            case 0x02:
            case 0x0e:
            case 0x06:
                QMessageBox::warning(this, "Color Conflict", "The background color conflicts with the module’s color scheme (red, blue, and light blue).\nPlease adjust the background to ensure proper visibility and consistency.");
                break;
            default:
                break;
            }
            setUltimate(romVec, ui->textColor->currentIndex());
            break;
        }

        // Ultimate Enhanced
        case 0xa81:
        {
            unsigned char bufTop[9] = {};
            unsigned char bufBottom[9] = {};
            QString topline, bottomline;
            topline = ultimatesettings->topLine();
            bottomline = ultimatesettings->bottomLine();

            if(topline.length()>0)
            {
                QByteArray bTopText = topline.toUtf8();
                memcpy(bufTop, bTopText.constData(), qMin((int)sizeof(bufTop), bTopText.size()));
            }
            else
                bufTop[0]=0x00;

            if(bottomline.length()>0)
            {
                QByteArray bBottomText = bottomline.toUtf8();
                memcpy(bufBottom, bBottomText.constData(), qMin((int)sizeof(bufBottom), bBottomText.size()));
            }
            else
                bufBottom[0]=0x00;

            setUltimateEnhanced(romVec,
                                       ui->textColor->currentIndex(),
                                       ultimatesettings->majorColorIndex(),
                                       ultimatesettings->minorColorIndex(),
                                       ultimatesettings->topColorIndex(),
                                       ultimatesettings->bottomColorIndex(),
                                       ultimatesettings->topLineColorIndex(),
                                       bufTop,
                                       ultimatesettings->bottomLineColorIndex(),
                                       bufBottom);
            break;
        }

        // Commodore Text
        case 0xb00:
        {
            setCommodoreText(romVec,
                                ui->textColor->currentIndex(),
                                commodoreetextsettings->topLineColorIndex(),
                                commodoreetextsettings->bottomLineColorIndex());
            break;
        }

        // Commodore Text Monochrome
        case 0xb01:
        {
            setCommodoreTextMono(romVec,
                             ui->textColor->currentIndex());
            break;
        }



        // DOS with READY.
        case 0x300:
        {
            if(!setDos(romVec)){
                QMessageBox::critical(this,
                                     invalidrom,
                                     nojiffydos);
                return;
            }
            break;
        }

        // DOS with OK
        case 0x301:
        {
            if(!setDos(romVec, true)){
                QMessageBox::critical(this,
                                      invalidrom,
                                      nojiffydos);
                return;
            }
            break;
        }

        // DOS with READY. Capitalized
        case 0x302:
        {
            if(!setCDos(romVec)){
                QMessageBox::critical(this,
                                      invalidrom,
                                      nojiffydos);
                return;
            }
            break;
        }

        // DOS with OK Capitalized
        case 0x303:
        {
            if(!setCDos(romVec, true)){
                QMessageBox::critical(this,
                                      invalidrom,
                                      nojiffydos);
                return;
            }
            break;
        }

        // JiffyDOS Logo
        case 0x100:
        {
            if(isJiffy(romVec)) {

                unsigned char buf[7] = {};
                QString qYourText="";

                switch(jiffydoslogoSettings->rightTextIndex())
                {
                    case 0: qYourText="V6.01";
                        break;

                    case 1:
                        qYourText = jiffydoslogoSettings->yourText();
                        break;

                    case 2: break;

                    default: break;
                }

                if(qYourText.length()>0)
                {
                    QByteArray bYourText = qYourText.toUtf8();
                    memcpy(buf, bYourText.constData(), qMin((int)sizeof(buf), bYourText.size()));
                }
                else
                    buf[0]=0x00;
                setJiffyDosLogoSettings(romVec, jiffydoslogoSettings->c64Text(), buf, jiffydoslogoSettings->noblink());
            }
            else
            {
                QMessageBox::critical(this, invalidrom, "The selected ROM file is not a JiffyDOS ROM. Please select a valid JiffyDOS ROM file.");
                return;
            }
                break;
        }

        //------------------
        default:
            break;
    }

    QString saveFileName(tempDir()+"temp.bin");

    if(!test)
    {
        saveFileName = QFileDialog::getSaveFileName(
            this,
            "Save Modified ROM",
            "",
            "ROM Files (*.bin *.rom);;All Files (*)"
            );

        if (saveFileName.isEmpty())
            return;
    }

    QFile outFile(saveFileName);
    // std::vector -> QByteArray
    QByteArray result(reinterpret_cast<const char*>(romVec.data()),
                      static_cast<qsizetype>(romVec.size()));

    if (!outFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "File could not be saved.");
        return;
    }

    outFile.write(result);
    outFile.close();

    if(!test)
        QMessageBox::information(this, "Saved", "Modified ROM saved successfully.");
    else
        launchApp(ui->EmulatorPath->text(), saveFileName, ui->ChargenPath->text()); // test rom only with emulator
}

void MainWindow::launchApp(const QString &appPath, const QString &romPath, const QString &chargenPath)
{
    QProcess *process = new QProcess(qApp);

    QStringList args;
    args << "-kernal" << romPath;
    if(!chargenPath.isEmpty()) args << "-chargen" << chargenPath;

    process->start(appPath, args);

    if (!process->waitForStarted(3000)) {
        QMessageBox::critical(this, "Error", "Could not launch the emulator. Please define the emulator in the settings.\n" + process->errorString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Open Kernal file
void MainWindow::on_openRomButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Select 8KB ROM File",
        "",
        "ROM Files (*.bin *.rom);;All Files (*)"
    );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "File could not be opened.");
        return;
    }

    ui->mainStackedWidget->setCurrentIndex(0);
    ui->info2->setEnabled(false);
    ui->gColors->setEnabled(false);
    ui->bPatch->setEnabled(false);
    ui->saveRomButton->setEnabled(false);
    ui->bTestRomFile->setEnabled(false);
    ui->bDefaultColors->setEnabled(false);
    ui->preview->setPixmap(QPixmap(":/res/pictures/monitoroff.png"));

    QByteArray data = file.readAll();
    file.close();

    if (data.size() != 8192) {
        QMessageBox::warning(this, "Invalid Size",
                             "File must be exactly 8KB (8192 bytes).");
        return;
    }

    romData = data;
    // QByteArray -> std::span (kopyasız)
    view = RomView(
        reinterpret_cast<const uint8_t*>(romData.constData()),
        romData.size()
    );

    getKernalRomImage();

    if (!romLoaded){
        QMessageBox::warning(this, "Unknown ROM File", "Unknown ROM file cannot be processed.");
        return;
    }

    dBorder = getBorderColor(view);
    dBackground = getBackgroundColor(view);
    dText = getTextColor(view);

    setDefaultColors();

    ui->preview->setPixmap(QPixmap(":/res/pictures/monitor.png"));

    ui->info2->setEnabled(true);
    ui->gColors->setEnabled(true);
    ui->bPatch->setEnabled(true);
    ui->saveRomButton->setEnabled(true);
    ui->bTestRomFile->setEnabled(true);
    ui->bDefaultColors->setEnabled(true);
    ui->selectedPatch->setText("No module has been selected yet.");

    ui->romfilename->setText("<html><head/><body><p><span style=\" font-weight:700;\">Opened File<br/></span>" + fileName + "</p></body></html>");
    on_bBack_clicked();

}

// Save as Kernal file
void MainWindow::on_saveRomButton_clicked()
{
    setupRom(false);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::onCardClicked(const CardItem &item)
{
    m_detailPage->setCard(item);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onBackRequested()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onApplyRequested()
{
    selectedModuleName = m_detailPage->currentItem().moduleName;
    QString selected = "<html><head/><body><p><b>Selected Module for KERNAL Patch</b><br/>";
    selected.append(m_detailPage->currentItem().name);
    selected.append("</p></body></html>");

    baName = selectedModuleName.toUtf8();

    // do not use xxx.toUtf8().constData()

    //if(license_validate(baDir.constData(), baName.constData()))
    //{
        ui->selectedPatch->setText(selected);
        selectedModuleIndex = m_detailPage->currentItem().moduleIndex;
    //}
    //else
    //    QMessageBox::critical(this, "Invalid License", "This module requires a valid license");
}

void MainWindow::onAdvancedSettingsRequested()
{
    onApplyRequested();
    switch (selectedModuleIndex)
    {
        case 0x004: dialog->exec(); break;
        case 0x100: jiffydoslogoSettings->exec(); break;
        case 0x580:{
            commodorelogoSettings->setScreenColors(ui->borderColor->currentColor(), ui->backgroundColor->currentColor(), ui->textColor->currentColor());
            commodorelogoSettings->exec();
            break;
        }
        case 0x581:{
            commodore64logoSettings->setScreenColors(ui->borderColor->currentColor(), ui->backgroundColor->currentColor(), ui->textColor->currentColor());
            commodore64logoSettings->exec();
            break;
        }

        case 0xa81:
        {
            ultimatesettings->setScreenColors(ui->borderColor->currentColor(), ui->backgroundColor->currentColor(), ui->textColor->currentColor());
            ultimatesettings->exec();
            break;
        }

        case 0xb00:
        {
            commodoreetextsettings->setScreenColors(ui->borderColor->currentColor(), ui->backgroundColor->currentColor(), ui->textColor->currentColor());
            commodoreetextsettings->exec();
            break;
        }

        case 0x900:
        {
            horizontalColorBarsSettings->setScreenColors(ui->borderColor->currentColor(), ui->backgroundColor->currentColor(), ui->textColor->currentColor());
            horizontalColorBarsSettings->exec();
            break;
        }

        default:
            break;
    }
}

void MainWindow::onUnlockRequested()
{
    QDesktopServices::openUrl(QUrl(m_detailPage->currentItem().url));
}

void MainWindow::onWhyunlockRequested()
{
    QMessageBox::information(this, "Why Unlock?", "Some modules are free, others require a small payment to unlock. Developing and maintaining these modules takes time and passion — every unlock helps keep this project alive. Thanks for your support!");
}

void MainWindow::on_bDefaultColors_clicked()
{
    setDefaultColors();
}

void MainWindow::on_bPatch_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(1);
    ui->bBack->setVisible(true);
    ui->bPatch->setVisible(false);
}

void MainWindow::on_info1_linkActivated(const QString &link)
{
    if (link=="info://more...")
    {
        ui->mainStackedWidget->setCurrentIndex(2); // more info
        ui->bBack->setVisible(true);
        ui->bPatch->setVisible(false);
        ui->saveRomButton->setVisible(false);
        ui->bTestRomFile->setVisible(false);
    }
}

void MainWindow::on_bBack_clicked()
{
    ui->bBack->setVisible(false);
    ui->bPatch->setVisible(true);
    ui->saveRomButton->setVisible(true);
    ui->bTestRomFile->setVisible(true);
    ui->mainStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionRewrite_the_Moment_of_Power_triggered()
{
    on_info1_linkActivated("info://more...");
}

void MainWindow::on_action_getroms_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.zimmers.net/anonftp/pub/cbm/firmware/computers/c64/index.html"));
}

void MainWindow::on_actionSettings_triggered()
{
    ui->mainStackedWidget->setCurrentIndex(3);
    ui->bBack->setVisible(true);
    ui->bPatch->setVisible(false);
    ui->saveRomButton->setVisible(false);
    ui->bTestRomFile->setVisible(false);
}

void MainWindow::on_bSaveSettings_clicked()
{
    QString emuPath = ui->EmulatorPath->text();
    QString chaPath = ui->ChargenPath->text();

    if(!QFile::exists(emuPath)){
        QMessageBox::critical(this, "Invalid Emulator File Path", "The file path entered for the emulator does not exist.");
        return;
    }
    if (!chaPath.isEmpty() && !QFile::exists(chaPath)) {
        QMessageBox::critical(this, "Invalid ROM File Path", "The entered C64 Chargen ROM file does not exist.");
        return;
    }
    ui->lSettingsSaved->setVisible(true);
    timer->start(3000);
    settings.setValue("EmulatorPath", emuPath);
    settings.setValue("ChargenPath", chaPath);
}

#ifdef Q_OS_MACOS
void changePathForMacOSAppFile(QString &AppFilePath)
{
    QFileInfo fi(AppFilePath);
    QString fiFilename = fi.fileName();
    if(fiFilename.right(4) == ".app") AppFilePath += "/Contents/MacOS/" + fiFilename.left(fiFilename.length()-4);
}
#endif

void MainWindow::on_bEmulatorPath_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName(this, tr("Select Emulator"),
                                                       appLocalDir(),
#ifdef Q_OS_WIN
                                                       tr("Emulator Application (*.exe);;Emulator Application (*.jar)"
#else
                                                       tr("Emulator Application (*)"
#endif
                                                          ));
    if (strFileName.isEmpty()) return;
#ifdef Q_OS_MACOS
    changePathForMacOSAppFile(strFileName);
#endif

#ifdef Q_OS_WIN
    strFileName = QDir::toNativeSeparators(strFileName);
#endif
    ui->EmulatorPath->setText(strFileName);
}


void MainWindow::on_bTestRomFile_clicked()
{
    setupRom(true);
}

// IMPORT ZIP AND M64 FILES VIA DRAG-DROP
QString MainWindow::modulesPath() const
{
#ifdef Q_OS_MACOS
    return QDir(QCoreApplication::applicationDirPath()).filePath("../Resources/modules/");
#else
    return QDir(QApplication::applicationDirPath()).filePath("modules");
#endif
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (!event->mimeData()->hasUrls()) {
        event->ignore();
        return;
    }

    for (const QUrl &url : event->mimeData()->urls()) {
        QString ext = QFileInfo(url.toLocalFile()).suffix().toLower();
        if (ext == "zip" || ext == "m64") {
            event->acceptProposedAction();
            return;
        }
    }

    event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    for (const QUrl &url : event->mimeData()->urls()) {
        if (!url.isLocalFile()) continue;

        QString path = url.toLocalFile();
        QString ext  = QFileInfo(path).suffix().toLower();

        if (ext == "zip")
            extractZip(path);
        else if (ext == "m64")
            copyM64(path);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize newSize = event->size();
    settings.setValue("Width", newSize.width());
    settings.setValue("Height", newSize.height());
    QMainWindow::resizeEvent(event);
}

void MainWindow::extractZip(const QString &zipPath)
{
    QString target = modulesPath();
    QDir().mkpath(target);

    QProcess proc;

#if defined(Q_OS_WIN)
    proc.setProgram("powershell");
    proc.setArguments({
        "-NoProfile", "-NonInteractive", "-Command",
        QString("Expand-Archive -Force -LiteralPath '%1' -DestinationPath '%2'")
            .arg(zipPath, target)
    });
#else
    proc.setProgram("unzip");
    proc.setArguments({"-o", zipPath, "-d", target});
#endif

    proc.start();
    proc.waitForFinished(60000);

    if (proc.exitCode() == 0) {
        QMessageBox::information(this, "Success",
                                 QString("The valid licenses have been loaded from the %1 file.")
                                     .arg(QFileInfo(zipPath).fileName()));
        loadItems();
    } else {
        QMessageBox::critical(this, "Error",
                              QString("The %1 file could not be extracted.")
                                  .arg(QString::fromLocal8Bit(proc.readAllStandardError()).trimmed()));
    }
}

void MainWindow::copyM64(const QString &filePath)
{
    QString target   = modulesPath();
    QDir().mkpath(target);

    QString fileName = QFileInfo(filePath).fileName();
    QString destPath = QDir(target).filePath(fileName);

    if (QFile::exists(destPath))
        QFile::remove(destPath);

    if (QFile::copy(filePath, destPath)) {
        QMessageBox::information(this, "Success",
                                 QString("The valid licenses have been loaded from the %1 file.").arg(fileName));
        loadItems();
    } else {
        QMessageBox::critical(this, "Error",
                              QString("%1 could not be copied.").arg(fileName));
    }
}

void MainWindow::onTimer()
{
    ui->lSettingsSaved->setVisible(false);
    timer->stop();
}

void MainWindow::on_actionLoad_a_module_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Load Module"),                           // Title
        QString(),                                   // Starting directory (empty = last used)
        tr("Module Files (*.m64 *.zip);;"            // Filter
           "M64 Files (*.m64);;"
           "ZIP Files (*.zip)")
        );

    if (filePath.isEmpty())
        return; // User cancelled

    if (filePath.endsWith(".m64", Qt::CaseInsensitive)) {
        copyM64(filePath);
    } else if (filePath.endsWith(".zip", Qt::CaseInsensitive)) {
        extractZip(filePath);
    }
}

void MainWindow::on_actionC_Balloon_Sprite_toggled(bool checked)
{
    checked ? m_sprite->start() : m_sprite->stop();
    settings.setValue("Balloon", checked);
}


void MainWindow::on_label_10_linkActivated(const QString &link)
{
    if(link=="VICE")
    {
        QDesktopServices::openUrl(QUrl("https://vice-emu.sourceforge.io/index.html#download"));
    }
}

void MainWindow::on_bChargenPath_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName(this, tr("Select Custom Chargen ROM File"),
                                                       appLocalDir(),
#ifdef Q_OS_WIN
                                                       tr("Chargen ROM Files (*.bin *.rom);;All Files (*)"
#else
                                                       tr("Chargen File (*)"
#endif
                                                          ));
    if (strFileName.isEmpty()) return;
#ifdef Q_OS_MACOS
    changePathForMacOSAppFile(strFileName);
#endif

#ifdef Q_OS_WIN
    strFileName = QDir::toNativeSeparators(strFileName);
#endif

    ui->ChargenPath->setText(strFileName);
}

void MainWindow::setScreenPreviewColors()
{
    QImage img(":/res/pictures/preview.png");
    ColorReplacer cr(img);

    // screen
    cr.replaceColor(QColor(255,200,255), ui->borderColor->currentColor());
    cr.replaceColor(QColor(255,210,210), ui->backgroundColor->currentColor());
    cr.replaceColor(QColor(129,51,56), ui->textColor->currentColor());

    ui->previewcolors->setPixmap(QPixmap::fromImage(cr.image()));
    ui->minipreviewcolors->setPixmap(QPixmap::fromImage(cr.image()));
}

void MainWindow::on_actionAbout_triggered()
{
    about->exec();
}

void MainWindow::on_actionModule_Store_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.c64kernal.com/modules"));
}

