#include "startbutton.h"

StartButton::StartButton(QWidget *parent) : QPushButton(parent)
{

}

void StartButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect(0, 0, width(), height());
    if(on)
    {
        painter.drawImage(rect, onImage);
    }
    else
    {
        painter.drawImage(rect, offImage);
    }
}

void StartButton::setOn(bool b)
{
    on = b;
    update();
}
