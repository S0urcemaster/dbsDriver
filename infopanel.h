#ifndef INFOPANEL_H
#define INFOPANEL_H
#include <QWidget>
#include "gearbox.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

/**
 * @brief The InfoPanel class
 * Multi-state display
 */
class InfoPanel : public QWidget
{
    Q_OBJECT

    QImage backCamImage{":/oma2.png"};
    QImage mapImage{":/Map2.png"};
    QFont fontH1;
    QFont fontP;

    double mileage{};
    double trip{};
    double consumption{};
    double average{};

    bool light{false};

    string state = KEYS;

public:
    static const string KEYS;
    static const string INFO;
    static const string NAVI;
    static const string REAR;

    explicit InfoPanel(QWidget *parent = nullptr);

    void setState(string);
    void toggleInfo();
    void toggleNavi();

    void setMileage(double);
    void setTrip(double);
    void setConsumption(double);
    void setAverage(double);

protected:
    void paintEvent(QPaintEvent* e) override;

public:
    void setLight(bool);

signals:

};

#endif // INFOPANEL_H





