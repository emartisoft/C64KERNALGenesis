#include "commodoretextsettings.h"
#include "ui_commodoretextsettings.h"

#include "changecolor.h"

CommodoreTextSettings::CommodoreTextSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommodoreTextSettings)
{
    setModal(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog
                   | Qt::CustomizeWindowHint
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint);

    ui->setupUi(this);
    ui->cTopLine->setCurrentIndex(13);
    ui->cBottomLine->setCurrentIndex(5);
    m_topColor = 13;
    m_bottomColor = 5;
    setColorsForImage();
    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

CommodoreTextSettings::~CommodoreTextSettings()
{
    delete ui;
}

void CommodoreTextSettings::setScreenColors(QColor border, QColor background, QColor text)
{
    m_border = border;
    m_background = background;
    m_text = text;
    setColorsForImage();
}

void CommodoreTextSettings::setColorsForImage()
{
    QImage img(":/res/pictures/commodoretext.png");
    ColorReplacer cr(img);
    // screen
    cr.replaceColor(QColor(255,200,255), m_border);
    cr.replaceColor(QColor(255,210,210), m_background);
    cr.replaceColor(QColor(235,255,220), m_text);
    // logo
    cr.replaceColor(QColor(220,250,255), ui->cTopLine->currentColor());
    cr.replaceColor(QColor(240,230,220), ui->cBottomLine->currentColor());

    ui->preview->setPixmap(QPixmap::fromImage(cr.image()));
}

void CommodoreTextSettings::on_bOK_clicked()
{
    accept();
}


void CommodoreTextSettings::on_cTopLine_currentIndexChanged(int index)
{
    m_topColor = index;
    setColorsForImage();
}


void CommodoreTextSettings::on_cBottomLine_currentIndexChanged(int index)
{
    m_bottomColor = index;
    setColorsForImage();
}

