#include "commodore64logosettings.h"
#include "ui_commodore64logosettings.h"

#include "changecolor.h"

CommodoreLogo64Settings::CommodoreLogo64Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommodoreLogo64Settings)
{
    setModal(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog
                   | Qt::CustomizeWindowHint
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    ui->c1->setCurrentIndex(14);
    ui->c2->setCurrentIndex(2);
    ui->cTopLine->setCurrentIndex(0);
    ui->cBottomLine->setCurrentIndex(0);
    m_topColor = 0;
    m_bottomColor = 0;

    ui->cTop64->setCurrentIndex(15);
    ui->cBottom64->setCurrentIndex(8);


    connect(ui->c1, &QComboBox::currentIndexChanged, this, [=]() {
        setColorsForImage();
    });
    connect(ui->c2, &QComboBox::currentIndexChanged, this, [=]() {
        setColorsForImage();
    });
    connect(ui->cTop64, &QComboBox::currentIndexChanged, this, [=]() {
        setColorsForImage();
    });
    connect(ui->cBottom64, &QComboBox::currentIndexChanged, this, [=]() {
        setColorsForImage();
    });
    setColorsForImage();

    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

CommodoreLogo64Settings::~CommodoreLogo64Settings()
{
    delete ui;
}

void CommodoreLogo64Settings::setScreenColors(QColor border, QColor background, QColor text)
{
    m_border = border;
    m_background = background;
    m_text = text;
    setColorsForImage();
}

void CommodoreLogo64Settings::setColorsForImage()
{
    QImage img(":/res/pictures/commodore64logo.png");
    ColorReplacer cr(img);
    m_major = ui->c1->currentIndex();
    m_minor = ui->c2->currentIndex();
    m_top64Color = ui->cTop64->currentIndex();
    m_bottom64Color = ui->cBottom64->currentIndex();

    // screen
    cr.replaceColor(QColor(255,200,255), m_border);
    cr.replaceColor(QColor(255,210,210), m_background);
    cr.replaceColor(QColor(255,239,197), m_text);
    // logo
    cr.replaceColor(QColor(220,250,255), ui->c1->currentColor());
    cr.replaceColor(QColor(235,235,255), ui->c2->currentColor());
    // 64
    cr.replaceColor(QColor(235,255,220), ui->cTop64->currentColor());
    cr.replaceColor(QColor(240,230,220), ui->cBottom64->currentColor());

    ui->preview->setPixmap(QPixmap::fromImage(cr.image()));
}


void CommodoreLogo64Settings::on_bOK_clicked()
{
    accept();
}


void CommodoreLogo64Settings::on_lTopline_textChanged(const QString &arg1)
{
    m_topline = arg1;
    ui->lTopline->setText(arg1.toUpper());
}


void CommodoreLogo64Settings::on_lBottomLine_textChanged(const QString &arg1)
{
    m_bottomline = arg1;
    ui->lBottomLine->setText(arg1.toUpper());
}


void CommodoreLogo64Settings::on_cTopLine_currentIndexChanged(int index)
{
    m_topColor = index;
}


void CommodoreLogo64Settings::on_cBottomLine_currentIndexChanged(int index)
{
    m_bottomColor = index;
}

