#include "horizontalcolorbarssettings.h"
#include "ui_horizontalcolorbarssettings.h"

#include "changecolor.h"

horizontalcolorbarssettings::horizontalcolorbarssettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::horizontalcolorbarssettings)
{
    setModal(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog
                   | Qt::CustomizeWindowHint
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    ui->cTopLine->setCurrentIndex(2);
    ui->cBottomLine->setCurrentIndex(5);
    ui->cCenterLine->setCurrentIndex(7);
    m_topColor = 2;
    m_bottomColor = 5;
    m_centerColor = 7;
    setColorsForImage();
    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

horizontalcolorbarssettings::~horizontalcolorbarssettings()
{
    delete ui;
}

void horizontalcolorbarssettings::setScreenColors(QColor border, QColor background, QColor text)
{
    m_border = border;
    m_background = background;
    m_text = text;
    setColorsForImage();
}

void horizontalcolorbarssettings::on_bOK_clicked()
{
    accept();
}

void horizontalcolorbarssettings::setColorsForImage()
{
    QImage img(":/res/pictures/horizontalcolorbars.png");
    ColorReplacer cr(img);
    // screen
    cr.replaceColor(QColor(255,200,255), m_border);
    cr.replaceColor(QColor(255,210,210), m_background);
    cr.replaceColor(QColor(255,239,197), m_text);
    // logo
    cr.replaceColor(QColor(220,250,255), ui->cTopLine->currentColor());
    cr.replaceColor(QColor(255,125,255), ui->cBottomLine->currentColor());
    cr.replaceColor(QColor(235,235,255), ui->cCenterLine->currentColor());

    ui->preview->setPixmap(QPixmap::fromImage(cr.image()));
}


void horizontalcolorbarssettings::on_cCenterLine_currentIndexChanged(int index)
{
    m_centerColor = index;
    setColorsForImage();
}


void horizontalcolorbarssettings::on_cTopLine_currentIndexChanged(int index)
{
    m_topColor = index;
    setColorsForImage();
}


void horizontalcolorbarssettings::on_cBottomLine_currentIndexChanged(int index)
{
    m_bottomColor = index;
    setColorsForImage();
}

