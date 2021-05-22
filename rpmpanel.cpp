#include "rpmpanel.h"

RpmPanel::RpmPanel(QWidget *parent) : RoundPanel(parent)
{
}

void RpmPanel::setRpm(double rpm)
{
    double degreeRange = RoundPanel::getMaxDegree() - RoundPanel::getMinDegree();
    setDegree((degreeRange / maxRpm) *rpm + RoundPanel::getMinDegree());
    update();
}

void RpmPanel::paintEvent(QPaintEvent* event)
{
    RoundPanel::paintEvent(event);
}

void RpmPanel::paintScale()
{
    RoundPanel::paintScale(); //Call function in super class to draw background of scale

    QPen pen1;
    QPen pen2;
    //Changes color of text and lines depending on if engine is running or not
    if(isLight())
    {
        pen1.setColor(Qt::white);
        pen2.setColor(QColor(0xff, 0x00, 0x66));
    }
    else
    {
        pen1.setColor(Qt::gray);
        pen2.setColor(QColor(0x80, 0x00, 0x33));
    }
    pen1.setWidth(2);
    pen2.setWidth(2);
    getPainter()->setPen(pen1);
    getPainter()->rotate(RoundPanel::getMinDegree());

    // paint scale
    for (int i{0}; i < 10; i++)
    {
        if(i>5)
        {
            getPainter()->setPen(pen2); //Red pen for rpm above 6000
        }
        getPainter()->drawLine(this->width()/2-10, 0, (this->width()/2)-(this->width()/15), 0);
        //Rotate to then draw the next line
        getPainter()->rotate((RoundPanel::getMaxDegree() - RoundPanel::getMinDegree())/9);
    }

    getPainter()->resetTransform(); //Undo rotation() and transform() to draw numbers

    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    getPainter()->setFont(font);
    getPainter()->setPen(pen1); //White

    //Draw text "km/h"
    getPainter()->drawText(90, this->height()- 40, "RPM x 1000");

    //Draw numbers
    font.setPointSize(12);
    getPainter()->setFont(font);
    getPainter()->drawText(36, 180, "0");
    getPainter()->drawText(23, 135, "1");
    getPainter()->drawText(31, 92, "2");
    getPainter()->drawText(55, 58, "3");
    getPainter()->drawText(98, 35, "4");
    getPainter()->drawText(142, 35, "5");
    getPainter()->setPen(pen2); //Red for rpm above 6000
    font.setBold(true);
    getPainter()->setFont(font);
    getPainter()->drawText(185, 55, "6");
    getPainter()->drawText(212, 90, "7");
    getPainter()->drawText(222, 138, "8");
    getPainter()->drawText(207, 180, "9");
}

void RpmPanel::setMaxRpm(double maxRpm)
{
    this->maxRpm = maxRpm;
}






