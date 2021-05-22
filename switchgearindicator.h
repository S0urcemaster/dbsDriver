#ifndef SWITCHGEARINDICATOR_H
#define SWITCHGEARINDICATOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>

/**
 * @brief The SwitchGearIndicator class
 * High rpm indicator lamp
 */
class SwitchGearIndicator : public QWidget
{
    Q_OBJECT

    bool light{false};
    QImage bg{":/light_off.png"};
    QImage lightImg{":/yellow_light.png"};

protected:
    void paintEvent(QPaintEvent*) override;

public:
    explicit SwitchGearIndicator(QWidget *parent = nullptr);
    void setLight(bool);

};

#endif // SWITCHGEARINDICATOR_H
