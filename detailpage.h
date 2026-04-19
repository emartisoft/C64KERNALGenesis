#pragma once

#include <QWidget>
#include <QPushButton>
#include "carditem.h"
#include "gifwidget.h"

class QLabel;
class QTextEdit;

class DetailPage : public QWidget
{
    Q_OBJECT

public:
    explicit DetailPage(QWidget *parent = nullptr);

    void setCard(const CardItem &item);
    CardItem currentItem() const { return m_item; }

signals:
    void backRequested();
    void applyRequested();
    void unlockRequested();
    void whyunlockRequested();
    void advancedSettingsRequested();

private:
    void setupUi();
    CardItem    m_item;
    GifWidget   *m_heroLabel        = nullptr;
    QLabel      *m_nameLabel        = nullptr;
    QLabel      *m_commentLabel     = nullptr;
    QLabel      *m_detailLabel      = nullptr;
    QPushButton *unlockBtn          = nullptr;
    QPushButton *applyBtn           = nullptr;
    QPushButton *advancedSettingsBtn= nullptr;
    QLabel      *whyunlock          = nullptr;

};
