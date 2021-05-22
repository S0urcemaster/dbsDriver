#include "roundpanel.h"

RoundPanel::RoundPanel(QWidget *parent): QPushButton(parent)
{
}

void RoundPanel::paintEvent(QPaintEvent*)
{
    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true); //To draw smooth lines
    rectBg = new QRectF(0,0, this->width(), this->height()); //Rect as big as the widget
    center = new QPointF(this->width() /2, this->height() /2); //Center point of rectBg
    paintScale();
    paintNeedle();
    painter->end();
}

void RoundPanel::paintScale()
{
    // Only gradient in the base class
    QRadialGradient radG(*center, rectBg->width()/2, *center);
    radG.setColorAt(0.2, QColor(0x00, 0x00, 0x99));

    if(light)
    {
        radG.setColorAt(0.95, QColor(0x3B, 0x89, 0xBD));
    }
    else
    {
        radG.setColorAt(0.95, Qt::blue);
    }
    radG.setColorAt(1, Qt::transparent);

    painter->fillRect(*rectBg, radG);
    painter->translate(*center);
}

void RoundPanel::paintNeedle()
{
    // same for all children
    // draws a horizontal line then rotates the painter

    QBrush brush1(QColor(0x80, 0x00, 0x33));
    QBrush brush2(QColor(0x33, 0x00, 0x14));

    //Changes color of text and lines depending on if engine is running or not
    if(light)
    {
        brush1.setColor(QColor(0xff, 0x00, 0x66));
        brush2.setColor(QColor(0x80, 0x00, 0x33));
    }
    else
    {
        brush1.setColor(QColor(0x80, 0x00, 0x33));
        brush2.setColor(QColor(0x33, 0x00, 0x14));
    }
    painter->translate(width() /2, height() /2);
    painter->rotate(degree);
    painter->setPen(Qt::PenStyle::NoPen);

    if(width() < 300)
    {
        painter->fillRect(width() /2 - 80, -4, 40, 8, brush2);
        painter->fillRect(width() /2 -78, -2, 36, 4, brush1);
    }
    else
    {
        painter->fillRect(width() /2 -110, -4, 50, 8, brush2);
        painter->fillRect(width() /2 -108, -2, 46, 4, brush1);
    }
}

void RoundPanel::setLight(bool b)
{
    light = b;
}

//Engine on/off -> light on/off
bool RoundPanel::isLight()
{
    return light;
}

double RoundPanel::getMinDegree()
{
    return minDegree;
}

double RoundPanel::getMaxDegree()
{
    return maxDegree;
}

double RoundPanel::getDegree()
{
   return degree;
}

void RoundPanel::setDegree(double degree)
{
    this->degree = degree;
}

QPainter* RoundPanel::getPainter()
{
    return painter;
}

QPointF* RoundPanel::getCenter()
{
    return center;
}

