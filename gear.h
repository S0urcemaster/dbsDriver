#ifndef GEAR_H
#define GEAR_H

#include <string>

using namespace std;

/**
 * @brief The Gear class
 * Gear struct
 */
class Gear
{
    string name;
    double ratio;
    double rpmIncrease;
    double rpmDecrease;

public:
    explicit Gear(string name, double ratio, double inc, double dec);
    string getName();
    double getRatio();
    double getRpmIncrease();
    double getRpmDecrease();
};

#endif // GEAR_H
