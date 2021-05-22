#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QPaintEvent>
#include <ui_docDialog.h>
#include <enginecontrolunit.h>
#include "datamanagement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Connects view with controller
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    EngineControlUnit *ecu;
    DataManagement *data;

    QImage bg{":/leather black.jpg"};

private slots:
    void startEngine();
    void resetTrip();
    void toggleInfo();
    void toggleNavi();
    void setA();
    void setM();
    void showHelp();
    void tempoMinus();
    void tempoPlus();
    void tempoSetReset();

    /**
     * @brief updateUi
     * Connects to the ECU signal
     */
    void updateUi();

protected:
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent*) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};
#endif // MAINWINDOW_H




