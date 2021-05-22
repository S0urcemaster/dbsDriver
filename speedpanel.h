#ifndef SPEEDPANEL_H
#define SPEEDPANEL_H

#include <roundpanel.h>
#include <QPaintEvent>
#include <QPainter>

/**
 * @brief The SpeedPanel class
 * Speed-O-Meter
 */
class SpeedPanel : public RoundPanel
{
    Q_OBJECT
    double maxSpeed{};
    double tempo{50};
    bool tempoOn{false};

protected:
    void paintEvent(QPaintEvent*) override;

    /**
     * @brief paintScale
     * paintScale() draws lines, numbers and general text on the panel
     */
    void paintScale() override;

    void paintTempoLocator();

public:
    explicit SpeedPanel(QWidget *parent = nullptr);

    /**
     * @brief setSpeed
     * Changes variable 'degree' to a value corresponding to the speed
     * @param speed
     */
    void setSpeed(double speed);
    void setMaxSpeed(double speed);
    void setTempo(double tempo);
    void setTempo(bool onOff);

};

#endif // SPEEDPANEL_H






