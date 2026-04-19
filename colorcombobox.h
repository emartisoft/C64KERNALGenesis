#ifndef COLORCOMBOBOX_H
#define COLORCOMBOBOX_H

#include <QComboBox>
#include <QColor>

class ColorComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit ColorComboBox(QWidget *parent = nullptr);

    QColor currentColor() const;

private:
    void addColorItem(const QString &name, const QColor &color);
};

#endif // COLORCOMBOBOX_H
