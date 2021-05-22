#ifndef SHADEPANEL_H
#define SHADEPANEL_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

/**
 * @brief The ShadePanel class
 * Gradient on the background texture around displays
 */
class ShadePanel : public QWidget
{
    Q_OBJECT
    QString brightColor{"#333"};
    QString darkColor{"#111"};
    qreal gradientPoint{0.93};
    bool bright{false};

protected:
    void paintEvent(QPaintEvent* e) override;

public:
    explicit ShadePanel(QWidget *parent = nullptr);
    void setGradientPoint(qreal);
    void setBright(bool);

};

#endif // SHADEPANEL_H
