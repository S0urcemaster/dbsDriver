#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

/**
 * @brief The StartButton class
 * Start button graphics
 */
class StartButton : public QPushButton
{

    QImage offImage{":/start2.png"};
    QImage onImage{":/start1.png"};

    bool on{false};

protected:
    void paintEvent(QPaintEvent* e) override;

public:
    explicit StartButton(QWidget *parent = nullptr);
    void setOn(bool);
};

#endif // STARTBUTTON_H
