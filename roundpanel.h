#ifndef ROUNDPANEL_H
#define ROUNDPANEL_H

#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QDebug>

/**
 * @brief The RoundPanel class
 * Baseclass of Speed-O- and RPM-O-Meter
 */
class RoundPanel : public QPushButton
{
    Q_OBJECT

    const double minDegree{-210};
    const double maxDegree{30};
    double degree{minDegree};
    bool light{false};

    QPainter* painter;
    QRectF* rectBg;
    QPointF* center;

protected:
    QPainter* getPainter();
    QPointF* getCenter();
    double getDegree();
    double getMinDegree();
    double getMaxDegree();
    void setDegree(double);
    bool isLight();

    /**
     * @brief paintScale
     * Draws the background gradient. The scale is painted in individually.
     */
    virtual void paintScale();

    /**
     * @brief paintNeedle
     * Draws the needle. Same for the children.
     */
    void paintNeedle();

    void paintEvent(QPaintEvent* event) override;

public:
    explicit RoundPanel(QWidget *parent = nullptr);
    void setLight(bool);

};

#endif // ROUNDPANEL_H





