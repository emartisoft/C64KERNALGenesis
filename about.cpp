#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::About)
{
    setModal(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog
                   | Qt::CustomizeWindowHint
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    adjustSize();                         // fit to content
    setFixedSize(sizeHint());             // then lock it
}

About::~About()
{
    delete ui;
}

void About::on_bOK_clicked()
{
    accept();
}

