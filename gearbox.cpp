#include "gearbox.h"

Gearbox::Gearbox()
{

}
void Gearbox::switchUp()
{
    if(gearIndex < maxIndex) {
        gearIndex++;
        current = gears[gearIndex];
    }
}

void Gearbox::switchDown()
{
    if(gearIndex > 0) {
        gearIndex--;
        current = gears[gearIndex];
    }
}

Gear* Gearbox::getCurrent()
{
    return current;
}

double Gearbox::getAxis()
{
    return axis;
}

double Gearbox::getTyre()
{
    return tyre;
}

double Gearbox::previousRatio()
{
    if(gearIndex > 0) {
        return gears[gearIndex-1]->getRatio();
    }
    return gears[gearIndex]->getRatio();
}

double Gearbox::nextRatio()
{
    if(gearIndex < maxIndex) {
        return gears[gearIndex+1]->getRatio();
    }
    return gears[gearIndex]->getRatio();
}

Gear* Gearbox::getGearMax()
{

    return gears[maxIndex];

}

Gearbox::~Gearbox()
{
    for (auto gear: gears){
        delete gear;
    }
}
