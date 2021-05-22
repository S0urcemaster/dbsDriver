#ifndef GEARBOX_H
#define GEARBOX_H

#include <array>
#include <gear.h>
#include <QDebug>

using namespace std;

/**
 * @brief The Gearbox class
 * Gearbox struct and logic
 */
class Gearbox
{
    array<Gear*, 7> gears {
        new Gear("R", 8.47, 180, 60), new Gear("N", 0, 250, 150), new Gear("1", 8.47, 180, 60),
        new Gear("2", 4.54, 150, 50), new Gear("3", 2.678, 100, 33), new Gear("4", 1.954, 75, 25),
        new Gear("5", 1.401, 50, 17)
    };

    int gearIndex{1};
    int maxIndex{6};

    Gear* current{gears[gearIndex]};

    double axis{3200};
    double tyre{1993};

public:
    Gearbox();
    void switchUp();
    void switchDown();
    Gear* getCurrent();
    double getAxis();
    double getTyre();

    /**
     * @brief previousRatio
     * @return ratio of next gear
     */
    double previousRatio();

    /**
     * @brief nextRatio
     * @return ratio of previous gear
     */
    double nextRatio();

    /**
     * @brief getGearMax
     * @return highest gear
     */
    Gear* getGearMax();

    ~Gearbox();
};

#endif // GEARBOX_H
