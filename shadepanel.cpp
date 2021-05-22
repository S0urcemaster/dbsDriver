#include "shadepanel.h"

ShadePanel::ShadePanel(QWidget *parent) : QWidget(parent)
{
}

void ShadePanel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPoint center(width()/2,height()/2);
    QRadialGradient radG(center, width()/2, center);
    if(bright)
    {
        radG.setColorAt(gradientPoint, brightColor);
    }
    else
    {
        radG.setColorAt(gradientPoint, darkColor);
    }
    radG.setColorAt(1, Qt::transparent);
    painter.fillRect(0, 0, width(), height(), radG);

    if(width() == 413) // qnd
    {
        painter.setPen(QColor(0x55, 0x55, 0x55));
        painter.drawLine(20, 0, width() -20, 0);
        painter.setPen(QColor(0x44, 0x44, 0x44));
        painter.drawLine(20, 1, width() -20, 1);
        painter.setPen(QColor(0x44, 0x44, 0x44));
        painter.drawLine(20, height() -2, width() -20, height() -2);
        painter.setPen(QColor(0x55, 0x55, 0x55));
        painter.drawLine(20, height() -1, width() -20, height() -1);
    }
}

void ShadePanel::setGradientPoint(qreal p)
{
    gradientPoint = p;
}

void ShadePanel::setBright(bool b)
{
    bright = b;
}




