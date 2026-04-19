#include "advancedsettingsdialog.h"
#include "ui_advancedsettingsdialog.h"

AdvancedSettingsDialog::AdvancedSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdvancedSettingsDialog)
{
    setModal(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog
                   | Qt::CustomizeWindowHint
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint);

    ui->setupUi(this);
    ui->cursorColor->setCurrentIndex(0);

    on_bDefault_clicked();

    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

AdvancedSettingsDialog::~AdvancedSettingsDialog()
{
    delete ui;
}
/*
void AdvancedSettingsDialog::setYourtext(const QString &yourtext)
{
    m_yourText = yourtext;
    ui->lYourText->setText(yourtext);
}

void AdvancedSettingsDialog::setBootTextIndex(int boottextindex)
{
    m_boottextindex = boottextindex;
    switch (boottextindex)
    {
    case -1: ui->gBootText->setChecked(false);
    case 0: ui->rReady->setChecked(true);
    case 1: ui->rOk->setChecked(true);
    default: ui->gBootText->setChecked(true); break;
    }
}

void AdvancedSettingsDialog::setBeep(bool val)
{
    ui->cBeep->setChecked(val);
}

void AdvancedSettingsDialog::setNoBlink(bool val)
{
    ui->cNoBlink->setChecked(val);
}

void AdvancedSettingsDialog::setCursorColorIndex(int cursorcolorindex)
{
    ui->cursorColor->setCurrentIndex(cursorcolorindex);
}
*/
void AdvancedSettingsDialog::on_pushButton_clicked()
{
    accept();
}

void AdvancedSettingsDialog::on_cBeep_clicked(bool checked)
{
    m_beep = checked;
}

void AdvancedSettingsDialog::on_cNoBlink_clicked(bool checked)
{
    m_noblink = checked;
}

void AdvancedSettingsDialog::on_gBootText_clicked(bool checked)
{
    if(!checked) m_boottextindex = -1;
}


void AdvancedSettingsDialog::on_lYourText_textChanged(const QString &arg1)
{
    m_yourText = arg1;
    ui->lYourText->setText(arg1.toUpper());
}

void AdvancedSettingsDialog::on_cursorColor_currentIndexChanged(int index)
{
    m_cursorColorIndex = index;
}

void AdvancedSettingsDialog::on_bDefault_clicked()
{
    ui->lYourText->setText("");
    m_yourText="";

    ui->cBeep->setChecked(false);
    m_beep=false;

    ui->cNoBlink->setChecked(false);
    m_noblink=false;

    ui->cursorColor->setCurrentIndex(0);
    m_cursorColorIndex=0;

    ui->gBootText->setChecked(true);
    m_boottextindex=0;
    ui->rReady->setChecked(true);

    ui->gCursorColor->setChecked(false);
    m_hasCursorColor=false;
}

void AdvancedSettingsDialog::on_rReady_clicked(bool checked)
{
    if(checked) m_boottextindex = 0;
}

void AdvancedSettingsDialog::on_rOk_clicked(bool checked)
{
    if(checked) m_boottextindex = 1;
}

void AdvancedSettingsDialog::on_gCursorColor_clicked(bool checked)
{
    m_hasCursorColor = checked;
}

