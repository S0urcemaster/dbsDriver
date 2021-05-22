#include "switchgearindicator.h"

SwitchGearIndicator::SwitchGearIndicator(QWidget *parent) : QWidget(parent)
{
}

void SwitchGearIndicator::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect(0, 0, this->width(), this->height());

    painter.drawImage(rect, bg);

    if(light)
    {
        painter.drawImage(rect, lightImg);
    }
}

void SwitchGearIndicator::setLight(bool l)
{
    light = l;
    update();
}
