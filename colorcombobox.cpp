#include "colorcombobox.h"
#include <QPixmap>
#include <QIcon>
#include "coloritemdelegate.h"
#include <QAbstractItemView>

ColorComboBox::ColorComboBox(QWidget *parent)
    : QComboBox(parent)
{
    setItemDelegate(new ColorItemDelegate(this));
    setLabelDrawingMode(QComboBox::LabelDrawingMode::UseDelegate);

    setMouseTracking(true);
    view()->setMouseTracking(true);

    // C64 16-color palette (Pepto PAL)
    addItem("Black",        QColor(0x00, 0x00, 0x00));
    addItem("White",        QColor(0xFF, 0xFF, 0xFF));
    addItem("Red",          QColor(0x8d, 0x41, 0x2e));
    addItem("Cyan",         QColor(0x81, 0xd2, 0xe7));
    addItem("Purple",       QColor(0x94, 0x45, 0xb7));
    addItem("Green",        QColor(0x65, 0xb8, 0x45));
    addItem("Blue",         QColor(0x42, 0x2e, 0xad));
    addItem("Yellow",       QColor(0xe6, 0xfe, 0x74));
    addItem("Orange",       QColor(0x94, 0x62, 0x1f));
    addItem("Brown",        QColor(0x58, 0x49, 0x00));
    addItem("Light Red",    QColor(0xcc, 0x7d, 0x67));
    addItem("Dark Grey",    QColor(0x55, 0x55, 0x55));
    addItem("Grey",         QColor(0x87, 0x87, 0x87));
    addItem("Light Green",  QColor(0xb7, 0xff, 0x95));
    addItem("Light Blue",   QColor(0x87, 0x72, 0xf9));
    addItem("Light Grey",   QColor(0xba, 0xba, 0xba));

}

QColor ColorComboBox::currentColor() const
{
    return currentData().value<QColor>();
}
