#include "jiffydoslogosettings.h"
#include "ui_jiffydoslogosettings.h"

JiffyDOSLogoSettings::JiffyDOSLogoSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JiffyDOSLogoSettings)
{
    setModal(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog
                   | Qt::CustomizeWindowHint
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint);

    ui->setupUi(this);

    // object functions

    on_bDefault_clicked();

    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

JiffyDOSLogoSettings::~JiffyDOSLogoSettings()
{
    delete ui;
}

void JiffyDOSLogoSettings::on_okBtn_clicked()
{
    accept();
}

void JiffyDOSLogoSettings::on_bDefault_clicked()
{
    ui->cC64Text->setChecked(false);
    m_c64text=false;

    ui->lYourText->setText("");
    m_yourText="";

    ui->rNone->setChecked(true);
    m_rightTextIndex=2;

    m_noblink = false;
    ui->cNoBlink->setChecked(false);
}

void JiffyDOSLogoSettings::on_rV601_clicked(bool checked)
{
    if (checked) m_rightTextIndex = 0;
}

void JiffyDOSLogoSettings::on_rYourText_clicked(bool checked)
{
    if (checked) m_rightTextIndex = 1;
}

void JiffyDOSLogoSettings::on_rNone_clicked(bool checked)
{
    if (checked) m_rightTextIndex = 2;
}

void JiffyDOSLogoSettings::on_cC64Text_clicked(bool checked)
{
    m_c64text = checked;
}

void JiffyDOSLogoSettings::on_lYourText_textChanged(const QString &arg1)
{
    m_yourText = arg1;
    ui->lYourText->setText(arg1.toUpper());
    ui->rYourText->setChecked(true);
    m_rightTextIndex = 1;
}


void JiffyDOSLogoSettings::on_cNoBlink_clicked(bool checked)
{
    m_noblink = checked;
}

