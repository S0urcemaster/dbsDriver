#include "enginecontrolunit.h"

EngineControlUnit::EngineControlUnit(QObject* parent) : QThread(parent)
{
}

void EngineControlUnit::run()
{
    QElapsedTimer timer; // measure run time
    int waitTime = 1000 /30; // 30 FPS = should take 33ms per loop

    while(threadRunning)
    {
        timer.start();
        if(accelerating)
        {
            double inc = gearbox.getCurrent()->getRpmIncrease();

            if(automatic && (rpm +inc +1000) >maxRpm) // switch up when automatic
            {
                gearUp();
            }
            if((rpm +inc) > maxRpm)
            {
                rpm = maxRpm;
            }
            else // increase rpm when not going above max
            {
                rpm += inc -(speed/ airDrag);
            }
            updateSpeed();
        }
        else if(braking)
        {
            tempoSet = false;
            if(automatic && (rpm -brakeDec -500) <lowRpm && gearbox.getCurrent()->getName() != "N")
                 // switch down when automatic
            {
                gearDown();
            }
            else if((rpm -brakeDec) < 0)
            {
                rpm = 0;
            }
            else // decrease rpm when not going below 0
            {
                rpm -= brakeDec + (speed /airDrag);
            }
            updateSpeed();
        }
        else
        {
            if(engineRunning)
            {
                // decrease depending on current gear
                double dec = gearbox.getCurrent()->getRpmDecrease();
                if(automatic && (rpm -gearbox.getCurrent()->getRpmDecrease() -500) <lowRpm &&
                        gearbox.getCurrent()->getName() != "N")
                    // switch down when automatic
                {
                    gearDown();
                }
                else if(tempoSet && (speed >= tempo)) {
                    if((((((rpm -dec) /gearbox.getCurrent()->getRatio()) /gearbox.getAxis()) *gearbox.getTyre() *60) /1000) >=tempo)
                    {
                        rpm -= dec + (speed /airDrag);
                    }
                    else {
                        rpm = (tempo *gearbox.getAxis() *gearbox.getCurrent()->getRatio() *1000) /(gearbox.getTyre() *60);
                    }
                }
                else if((rpm -dec) < lowRpm) {
                    rpm = lowRpm;
                }
                else {
                    rpm -= dec + (speed /airDrag);
                }
                if(gearbox.getCurrent()->getName() != "N") {
                    updateSpeed();
                }
                else if (speed > 0) {
                    speed = speed -1;
                    if(speed < 1) {
                        speed = 0;
                    }
                }
            }
        }
        updateMileage();
        updateTrip();
        updateConsumption();
        updateAverage();

        emit updated(); // done-message to parent

        QThread::msleep(waitTime -timer.elapsed());
    }
}

void EngineControlUnit::startEngine()
{
    if(engineRunning && gearbox.getCurrent()->getName() == "N")
    {
        engineRunning = false;
        rpm = 0;
        speed = 0;
        braking = false;
        accelerating = false;
    }
    else
    {
        engineRunning = true;
    }
}

void EngineControlUnit::accelerate(bool b)
{
    if(!engineRunning)
    {
        return;
    }
    accelerating = b;
}

void EngineControlUnit::brake(bool b)
{
    if(!engineRunning)
    {
        return;
    }
    braking = b;
}

void EngineControlUnit::gearUp()
{
    if(!engineRunning)
    {
        return;
    }
    if(gearbox.getCurrent()->getName() == "N")
    {
        gearbox.switchUp();
        rpm = lowRpm;
        updateSpeed();
    }
    else if(gearbox.getCurrent()->getName() == "R")
    {
        gearbox.switchUp();
        rpm = lowRpm;
        speed = 0;
    }
    else
    {
        // check if we can switch up depending on the next gear's ratio in order to not deceed lowRpm
        double rpmNext = (speed *gearbox.getAxis() *gearbox.nextRatio() *1000) /(gearbox.getTyre() *60);
        if(rpmNext >= lowRpm)
        {
            gearbox.switchUp();
        }
        updateRpm();
    }
}

void EngineControlUnit::gearDown()
{
    if(!engineRunning)
    {
        return;
    }
    if(gearbox.getCurrent()->getName() == "N")
    {
        gearbox.switchDown();
        rpm = lowRpm;
        updateSpeed();
    }
    else if(gearbox.getCurrent()->getName() == "1")
    {
        gearbox.switchDown();
        //rpm = lowRpm;
        //speed = 0;
    }
    else
    {
        // check if we can switch down depending on the next gear's ratio in order to not exceed maxRpm
        double rpmPrevious = (speed *gearbox.getAxis() *gearbox.previousRatio() *1000) /(gearbox.getTyre() *60);
        if(rpmPrevious < maxRpm)
        {
            gearbox.switchDown();
        }
        updateRpm();
    }
}

void EngineControlUnit::updateRpm()
{
    rpm = (speed *gearbox.getAxis() *gearbox.getCurrent()->getRatio() *1000) /(gearbox.getTyre() *60);
}

void EngineControlUnit::updateSpeed()
{
    double ratio;
    if(gearbox.getCurrent()->getName() != "N") {
        ratio = gearbox.getCurrent()->getRatio();
        speed = (((rpm /ratio) /gearbox.getAxis()) *gearbox.getTyre() *60) /1000;
    }
}

void EngineControlUnit::updateMileage()
{
    mileage += speed * 0.000278 / 30;
}

void EngineControlUnit::updateTrip()
{
    trip += speed * 0.000278 / 30;
}

void EngineControlUnit::updateConsumption()
{
    if(accelerating) {
        //consumption = 8 *( speed / 50 ) * ( rpm / 6000 ) * ( rpm / 6000 );
        if(consumption +0.9 >20.7) {
            consumption = 20.7;
        }
        else
        {
            consumption += 0.9;
        }
    }
    else if(speed == tempo) {
        consumption = 20.7 *(rpm /maxRpm);
    }
    else if(rpm > lowRpm)
    {
        if(consumption -0.9 <0) {
            consumption = 0;
        }
        else
        {
            consumption -= 0.9;
        }
    }
    else {
        if(consumption -0.9 <1.8) {
            consumption = 1.8;
        }
        else
        {
            consumption -= 0.9;
        }
    }
}

void EngineControlUnit::updateAverage() {
    static long time{};
    average = ((average *time++) +consumption) /time;
}

double EngineControlUnit::getRpm()
{
    return rpm;
}

double EngineControlUnit::getMaxRpm()
{
    return maxRpm;
}

double EngineControlUnit::getSpeed()
{
    return speed;
}

Gear* EngineControlUnit::getGear()
{
    return gearbox.getCurrent();
}

bool EngineControlUnit::isRedRpm()
{
    return rpm >redRpm;
}

double EngineControlUnit::getMileage()
{
    return mileage;
}

double EngineControlUnit::getTrip()
{
    return trip;
}

double EngineControlUnit::getConsumption()
{
    return consumption;
}

double EngineControlUnit::getAverage() {
    return average;
}

double EngineControlUnit::getMaxSpeed()
{
    long maxSpeed = (((maxRpm /gearbox.getGearMax()->getRatio()) /gearbox.getAxis()) *gearbox.getTyre() *60) /1000;
    return maxSpeed;
}

bool EngineControlUnit::isEngineRunning()
{
    return engineRunning;
}

void EngineControlUnit::setMileage(double mileage)
{
    this->mileage = mileage;
}

void EngineControlUnit::setTrip(double trip)
{
    this->trip = trip;
}

void EngineControlUnit::setThreadRunning(bool r)
{
    threadRunning = r;
}

void EngineControlUnit::setAutomatic(bool b)
{
    automatic = b;
}

bool EngineControlUnit::getAutomatic()
{
    return automatic;
}


void EngineControlUnit::tempoSetReset() {
    tempoSet = !tempoSet;
}

bool EngineControlUnit::getTempoSet() {
    return tempoSet;
}

void EngineControlUnit::tempoPlus() {
    if(tempo +10 >130) {
        tempo = 130;
    }
    else
    {
        tempo += 10;
    }
}

void EngineControlUnit::tempoMinus() {
    if(tempo -10 <30)
    {
        tempo = 30;
    }
    else
    {
        tempo -= 10;
    }
}

double EngineControlUnit::getTempo() {
    return tempo;
}

EngineControlUnit::~EngineControlUnit()
{

}




