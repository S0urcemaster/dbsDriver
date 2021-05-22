#include "infopanel.h"

const string InfoPanel::KEYS = "keys";
const string InfoPanel::INFO = "info";
const string InfoPanel::NAVI = "navi";
const string InfoPanel::REAR = "rear";

InfoPanel::InfoPanel(QWidget *parent) : QWidget(parent)
{
    fontH1.setPointSize(15);
    fontP.setPointSize(12);
}

void InfoPanel::setState(string s)
{
    state = s;
}

void InfoPanel::toggleInfo()
{
    if(state == INFO)
    {
        state = KEYS;
    }
    else
    {
        state = INFO;
    }
}

void InfoPanel::toggleNavi()
{
    if(state == INFO)
    {
        state = NAVI;
    }
    else if(state == KEYS)
    {
        state = NAVI;
    }
    else
    {
        state = INFO;
    }
}

void InfoPanel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect rect(0, 0, width(), height());
    QPointF center(QPointF(rect.width() /2, rect.height() /2));

    QRadialGradient radG(center,rect.width()/2,center);
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

    if(light)
    {
        painter.setPen(Qt::white);
    }
    else
    {
        painter.setPen(Qt::gray);
    }

    if(state == REAR)
    {
        painter.drawImage(rect, backCamImage);
    }
    else if(state == INFO)
    {
        painter.fillRect(rect, radG);
        painter.setFont(fontH1);
        painter.drawText(50, 33,"Info");
        painter.setFont(fontP);
        painter.drawText(40, 60, "Trip");
        painter.drawText(40, 85, "Total");
        painter.drawText(40, 110, "Consumption");
        painter.drawText(40, 135, "Average");
        painter.drawText(160, 60, QString::number(trip,'f',1));
        painter.drawText(160, 85, QString::number(mileage,'f',1));
        painter.drawText(160, 110, QString::number(consumption,'f',1));
        painter.drawText(160, 135, QString::number(average,'f',1));
        painter.drawText(260, 60, "km");
        painter.drawText(260, 85, "km");
        painter.drawText(260, 110, "l/h");
        painter.drawText(260, 135, "l/100km");
    }
    else if(state == KEYS)
    {
        painter.fillRect(rect, radG);
        painter.setFont(fontH1);
        painter.drawText(50, 33, "Controls");
        painter.setFont(fontP);
        painter.drawText(40, 60, "Engine Start");
        painter.drawText(40, 80, "Accelerate");
        painter.drawText(40, 100, "Brake");
        painter.drawText(40, 120, "Gear Down");
        painter.drawText(40, 140, "Gear Up");
        painter.drawText(160, 60, "Return");
        painter.drawText(160, 80, "Home");
        painter.drawText(160, 100, "End");
        painter.drawText(160, 120, "PgUp");
        painter.drawText(160, 140, "PgDown");
        painter.drawText(260, 60, "Enter");
        painter.drawText(260, 80, "8");
        painter.drawText(260, 100, "5");
        painter.drawText(260, 120, "6");
        painter.drawText(260, 140, "4");
        painter.drawText(340, 60, "E");
        painter.drawText(340, 80, "W");
        painter.drawText(340, 100, "S");
        painter.drawText(340, 120, "D");
        painter.drawText(340, 140, "A");
    }
    else if(state == NAVI)
    {
        painter.drawImage(rect, mapImage);
    }
}

void InfoPanel::setLight(bool b)
{
    light = b;
    update();
}

void InfoPanel::setMileage(double mileage)
{
    this->mileage = mileage;
}

void InfoPanel::setTrip(double trip)
{
    this->trip = trip;
}

void InfoPanel::setConsumption(double consumption)
{
    this->consumption = consumption;
}

void InfoPanel::setAverage(double d) {
    average = d;
}




