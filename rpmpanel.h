#ifndef RPMPANEL_H
#define RPMPANEL_H

#include <roundpanel.h>

/**
 * @brief The RpmPanel class
 * RPM-O-Meter
 */
class RpmPanel : public RoundPanel
{
    Q_OBJECT

    double maxRpm{1};

protected:
    void paintEvent(QPaintEvent*) override;

    /**
     * @brief paintScale
     * paintScale() draws lines, numbers and general text on the panel
     */
    void paintScale() override;

public:
    explicit RpmPanel(QWidget *parent = nullptr);

    /**
     * @brief setRpm
     * Set rpm value and change variable 'degree' to a value corresponding to the rpm
     * @param rpm
     */
    void setRpm(double rpm);
    void setMaxRpm(double rpm);

};

#endif // RPMPANEL_H





