#include "commodorelogosettings.h"
#include "ui_commodorelogosettings.h"

#include "changecolor.h"

CommodoreLogoSettings::CommodoreLogoSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommodoreLogoSettings)
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

    connect(ui->c1, &QComboBox::currentIndexChanged, this, [=]() {
        setColorsForImage();
    });
    connect(ui->c2, &QComboBox::currentIndexChanged, this, [=]() {
        setColorsForImage();
    });
    setColorsForImage();

    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

CommodoreLogoSettings::~CommodoreLogoSettings()
{
    delete ui;
}

void CommodoreLogoSettings::setScreenColors(QColor border, QColor background, QColor text)
{
    m_border = border;
    m_background = background;
    m_text = text;
    setColorsForImage();
}

void CommodoreLogoSettings::setColorsForImage()
{
    QImage img(":/res/pictures/commodorelogo.png");
    ColorReplacer cr(img);
    m_major = ui->c1->currentIndex();
    m_minor = ui->c2->currentIndex();

    // screen
    cr.replaceColor(QColor(255,200,255), m_border);
    cr.replaceColor(QColor(255,210,210), m_background);
    cr.replaceColor(QColor(255,239,197), m_text);
    // logo
    cr.replaceColor(QColor(220,250,255), ui->c1->currentColor());
    cr.replaceColor(QColor(235,235,255), ui->c2->currentColor());

    ui->preview->setPixmap(QPixmap::fromImage(cr.image()));
}


void CommodoreLogoSettings::on_bOK_clicked()
{
    accept();
}


void CommodoreLogoSettings::on_lTopline_textChanged(const QString &arg1)
{
    m_topline = arg1;
    ui->lTopline->setText(arg1.toUpper());
}


void CommodoreLogoSettings::on_lBottomLine_textChanged(const QString &arg1)
{
    m_bottomline = arg1;
    ui->lBottomLine->setText(arg1.toUpper());
}


void CommodoreLogoSettings::on_cTopLine_currentIndexChanged(int index)
{
    m_topColor = index;
}


void CommodoreLogoSettings::on_cBottomLine_currentIndexChanged(int index)
{
    m_bottomColor = index;
}

