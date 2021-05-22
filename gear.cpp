#include "gear.h"

Gear::Gear(string name, double ratio, double rpmIncrease, double rpmDecrease)
    : name{name}, ratio{ratio}, rpmIncrease{rpmIncrease}, rpmDecrease{rpmDecrease}
{
}

string Gear::getName()
{
    return name;
}

double Gear::getRatio()
{
    return ratio;
}

double Gear::getRpmIncrease()
{
    return rpmIncrease;
}

double Gear::getRpmDecrease()
{
    return rpmDecrease;
}
