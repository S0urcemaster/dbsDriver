#include "speedpanel.h"

SpeedPanel::SpeedPanel(QWidget *parent) : RoundPanel(parent)
{
}

void SpeedPanel::setSpeed(double speed)
{
    double degreeRange = RoundPanel::getMaxDegree() - RoundPanel::getMinDegree();
    setDegree((degreeRange /maxSpeed) *speed + RoundPanel::getMinDegree());
    update();
}

void SpeedPanel::setMaxSpeed(double maxSpeed)
{
    this->maxSpeed = maxSpeed;
}

void SpeedPanel::setTempo(double d)
{
    tempo = d;
}

void SpeedPanel::setTempo(bool on) {
    tempoOn = on;
}

void SpeedPanel::paintEvent(QPaintEvent* event)
{
    RoundPanel::paintEvent(event);
}

void SpeedPanel::paintScale() {
    RoundPanel::paintScale(); //Call function in super class to draw background of scale
    paintTempoLocator();
    QPen pen1;
    if(isLight())
    {
        pen1.setColor(Qt::white); //Changes color of text and lines depending on if engine is running or not
    }
    else
    {
        pen1.setColor(Qt::gray);
    }
    pen1.setWidth(2);
    getPainter()->setPen(pen1);

    getPainter()->rotate(RoundPanel::getMinDegree()); //Set position of first line

    //Draw lines of scale
    for (int i{0}; i < 25; i++)
    {
        //Draw first and every second line longer
        if(i == 0 || i % 2 == 0 )
        {
            getPainter()->drawLine(this->width()/2-12, 0, (this->width()/2)-(this->width()/15), 0);
        }
        else
        {
            getPainter()->drawLine(this->width()/2-12, 0, (this->width()/2)-(this->width()/20), 0);
        }
        getPainter()->rotate((RoundPanel::getMaxDegree() - RoundPanel::getMinDegree())/24); //Rotate to then draw the next line
    }

    getPainter()->resetTransform(); //Undo rotation() and transform() to draw numbers
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    getPainter()->setFont(font);

    //Draw text "km/h"
    getPainter()->drawText(196, this->height() -50, "km/h");

    //Draw numbers
    getPainter()->drawText(60, 310, "0");
    getPainter()->drawText(40, 250, "20");
    getPainter()->drawText(40, 190, "40");
    getPainter()->drawText(60, 130, "60");
    getPainter()->drawText(100, 90, "80");
    getPainter()->drawText(145, 60, "100");
    getPainter()->drawText(200, 50, "120");
    getPainter()->drawText(260, 60, "140");
    getPainter()->drawText(310, 90, "160");
    getPainter()->drawText(345, 130, "180");
    getPainter()->drawText(365, 190, "200");
    getPainter()->drawText(365, 250, "220");
    getPainter()->drawText(345, 310, "240");
}


void SpeedPanel::paintTempoLocator()
{
    QPen penDark(QColor(0xaa, 0x99, 0x33));
    QPen penOff(QColor(0xbb, 0xbb, 0x33));
    QPen penOn(QColor(0xff, 0xee, 0x00));
    penOff.setWidth(7);
    penOn.setWidth(7);
    penDark.setWidth(7);
    if(!isLight())
    {
        getPainter()->setPen(penDark);

    }
    else if(tempoOn)
    {
        getPainter()->setPen(penOn);
    }
    else
    {
        getPainter()->setPen(penOff);
    }
    //Rotate to then draw the next line
    getPainter()->rotate(RoundPanel::getMinDegree());
    getPainter()->rotate(tempo);

    getPainter()->drawLine(this->width()/2-14, 0, (this->width()/2)-(this->width()/15), 0);
    getPainter()->resetTransform();
    getPainter()->translate(*getCenter());
}






