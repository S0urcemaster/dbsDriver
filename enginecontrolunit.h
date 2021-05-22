#ifndef ENGINECONTROLUNIT_H
#define ENGINECONTROLUNIT_H

#include <gearbox.h>
#include <QDebug>
#include <QThread>
#include <QElapsedTimer>
#include <QTimer>
#include <math.h>

/**
 * @brief The EngineControlUnit class
 * Does most of the logic and runs the 30fps update thread.
 */
class EngineControlUnit : public QThread
{
    Q_OBJECT

    bool threadRunning{true};
    bool accelerating{false};
    bool braking{false};
    bool shifting{false};

    double mileage{};
    double trip{};
    double consumption{};
    double average{};
    double rpm{};
    double maxRpm{9000};
    double lowRpm{800};
    double speed{};
    Gearbox gearbox;
    bool engineRunning{false};
    double brakeDec{150};
    double redRpm{6000};
    double airDrag{10};
    bool automatic{false};
    double tempo{50};
    bool tempoSet{false};

    /**
     * @brief updateSpeed
     * Calculate speed
     */
    void updateSpeed();

    /**
     * @brief updateRpm
     * Calculate rpm
     */
    void updateRpm();

    /**
     * @brief updateConsumption
     * Calculate consumption
     */
    void updateConsumption();

    /**
     * @brief updateMileage
     * Calculate mileage
     */
    void updateMileage();

    /**
     * @brief updateTrip
     * Calculate trip
     */
    void updateTrip();

    void updateAverage();

protected:
    void run() override;

public:
    explicit EngineControlUnit(QObject* parent);

    void setThreadRunning(bool);
    void startEngine();
    void accelerate(bool);
    void brake(bool);
    void gearUp();
    void gearDown();

    bool isEngineRunning();
    double getRpm();
    bool isRedRpm();
    double getMaxRpm();
    double getSpeed();
    Gear* getGear();
    double getMileage();
    void setMileage(double);
    double getTrip();
    void setTrip(double);
    double getConsumption();
    double getAverage();
    void setAutomatic(bool);
    bool getAutomatic();
    void tempoPlus();
    void tempoMinus();
    double getTempo();
    void tempoSetReset();
    bool getTempoSet();

    /**
     * @brief getMaxSpeed
     * @return speed at highest gear
     */
    double getMaxSpeed();

    ~EngineControlUnit();

signals:
    /**
     * @brief updated
     * Emitted by update thread when calculation is done.
     */
    void updated();

};

#endif // ENGINECONTROLUNIT_H




