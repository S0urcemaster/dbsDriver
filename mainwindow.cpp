#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonStart, &QPushButton::clicked, this, &MainWindow::startEngine);
    connect(ui->buttonInfo, &QPushButton::clicked, this, &MainWindow::toggleInfo);
    connect(ui->buttonNav, &QPushButton::clicked, this, &MainWindow::toggleNavi);
    connect(ui->buttonTrip, &QPushButton::clicked, this, &MainWindow::resetTrip);
    connect(ui->buttonA, &QPushButton::clicked, this, &MainWindow::setA);
    connect(ui->buttonM, &QPushButton::clicked, this, &MainWindow::setM);
    connect(ui->buttonTrip, &QPushButton::clicked, this, &MainWindow::resetTrip);
    connect(ui->buttonHelp, &QPushButton::clicked, this, &MainWindow::showHelp);
    connect(ui->buttonTempoMinus, &QPushButton::clicked, this, &MainWindow::tempoMinus);
    connect(ui->buttonTempoPlus, &QPushButton::clicked, this, &MainWindow::tempoPlus);
    connect(ui->buttonTempoSetReset, &QPushButton::clicked, this, &MainWindow::tempoSetReset);

    ecu = new EngineControlUnit(this);
    connect(ecu, &EngineControlUnit::updated, this, &MainWindow::updateUi);

    // initialize RoundPanels
    ui->rpmPanel->setMaxRpm(ecu->getMaxRpm());
    ui->speedPanel->setMaxSpeed(ecu->getMaxSpeed());

    // read start values from disk
    data = new DataManagement(this);
    data->readData();
    ecu->setMileage(data->getMileage());
    ecu->setTrip(data->getTrip());

    // run ECU Thread
    ecu->start();
}

void MainWindow::startEngine()
{
    ecu->startEngine();
    if(ecu->isEngineRunning()) // lights on
    {
        ui->infoPanel->setState(InfoPanel::INFO);
        ui->buttonStart->setOn(true);
        ui->dbsLabel->setStyleSheet("color:#ff0066");
        ui->shadePanel->setBright(true);
        ui->shadePanel2->setBright(true);
        ui->shadePanel3->setBright(true);
        ui->speedLcd->setStyleSheet("background:transparent;color:white");
        ui->gearLabel->setStyleSheet("background:transparent;color:white");
        ui->buttonA->setEnabled(true);
        ui->buttonInfo->setEnabled(true);
        ui->buttonM->setEnabled(true);
        ui->buttonNav->setEnabled(true);
        ui->buttonTrip->setEnabled(true);
    }
    else // lights off
    {
        ui->infoPanel->setState(InfoPanel::KEYS);
        ui->buttonStart->setOn(false);
        ui->dbsLabel->setStyleSheet("color:#800033");
        ui->shadePanel->setBright(false);
        ui->shadePanel2->setBright(false);
        ui->shadePanel3->setBright(false);
        ui->speedLcd->setStyleSheet("background:transparent;color:#333");
        ui->gearLabel->setStyleSheet("background:transparent;color:#999");
        ui->buttonA->setEnabled(false);
        ui->buttonInfo->setEnabled(false);
        ui->buttonM->setEnabled(false);
        ui->buttonNav->setEnabled(false);
        ui->buttonTrip->setEnabled(false);
    }
}

void MainWindow::resetTrip()
{
    ecu->setTrip(0);
}

void MainWindow::toggleInfo()
{
    ui->infoPanel->toggleInfo();
}

void MainWindow::toggleNavi()
{
    ui->infoPanel->toggleNavi();
}

void MainWindow::setA()
{
    ecu->setAutomatic(true);
    ui->buttonA->setStyleSheet("background: #333;color:#ff0066");
    ui->buttonM->setStyleSheet("background: #333;color:white");
}

void MainWindow::setM()
{
    ecu->setAutomatic(false);
    ui->buttonM->setStyleSheet("background: #333;color:#ff0066");
    ui->buttonA->setStyleSheet("background: #333;color:white");
}

void MainWindow::showHelp()
{
    static QDialog* doc{}; // singelton!
    if(!doc) {
        doc = new QDialog(this);
    }
    Ui_Dialog docUi;
    docUi.setupUi(doc);
    doc->show();
}


void MainWindow::tempoPlus() {
    ecu->tempoPlus();
    ui->speedPanel->setTempo(ecu->getTempo());
}

void MainWindow::tempoMinus() {
    ecu->tempoMinus();
    ui->speedPanel->setTempo(ecu->getTempo());
}

void MainWindow::tempoSetReset() {
    ecu->tempoSetReset();
    ui->speedPanel->setTempo(ecu->getTempoSet());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->isAutoRepeat()) // repeats can be ignored
    {
        return;
    }

    switch(event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_E:
        startEngine();
        break;
    case Qt::Key_Home:
    case Qt::Key_8:
    case Qt::Key_W:
    case Qt::Key_G:
        ecu->accelerate(true);
        ui->labelAcc->setStyleSheet("color:#ff0066");
        break;
    case Qt::Key_End:
    case Qt::Key_5:
    case Qt::Key_S:
    case Qt::Key_R:
        ecu->brake(true);
        ui->labelBra->setStyleSheet("color:#ff0066");
        break;
    case Qt::Key_PageUp:
    case Qt::Key_6:
    case Qt::Key_D:
    case Qt::Key_T:
        ecu->gearUp();
        if(ecu->isEngineRunning() && ecu->getGear()->getName() == "N") // return from rear cam
        {
            ui->infoPanel->setState(InfoPanel::INFO);
        }
        ui->labelSup->setStyleSheet("color:#ff0066");
        break;
    case Qt::Key_PageDown:
    case Qt::Key_4:
    case Qt::Key_A:
    case Qt::Key_N:
        ecu->gearDown();
        if(ecu->isEngineRunning() && ecu->getGear()->getName() == "R") // show rear cam
        {
            ui->infoPanel->setState(InfoPanel::REAR);
        }
        ui->labelSow->setStyleSheet("color:#ff0066");
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    switch(event->key())
    {
    case Qt::Key_Home:
    case Qt::Key_8:
    case Qt::Key_W:
    case Qt::Key_G:
        ecu->accelerate(false);
        ui->labelAcc->setStyleSheet("color:#333");
        break;
    case Qt::Key_End:
    case Qt::Key_5:
    case Qt::Key_S:
    case Qt::Key_R:
        ecu->brake(false);
        ui->labelBra->setStyleSheet("color:#333");
        break;
    case Qt::Key_PageUp:
    case Qt::Key_6:
    case Qt::Key_D:
    case Qt::Key_T:
        ui->labelSup->setStyleSheet("color:#333");
        break;
    case Qt::Key_PageDown:
    case Qt::Key_4:
    case Qt::Key_A:
    case Qt::Key_N:
        ui->labelSow->setStyleSheet("color:#333");
        break;
    }
}

void MainWindow::updateUi() // time to update the visuals
{
    ui->rpmPanel->setRpm(ecu->getRpm());
    ui->speedPanel->setSpeed(ecu->getSpeed());
    ui->speedLcd->display(ecu->getSpeed());
    ui->gearLabel->setText(QString::fromStdString(ecu->getGear()->getName()));
    ui->sgiWidget->setLight(ecu->isRedRpm());
    ui->infoPanel->setMileage(ecu->getMileage());
    ui->infoPanel->setTrip(ecu->getTrip());
    ui->infoPanel->setConsumption(ecu->getConsumption());
    ui->infoPanel->setAverage(ecu->getAverage());
    ui->speedPanel->setLight(ecu->isEngineRunning());
    ui->rpmPanel->setLight(ecu->isEngineRunning());
    ui->infoPanel->setLight(ecu->isEngineRunning());
    ui->speedPanel->setTempo(ecu->getTempo());
    ui->speedPanel->setTempo(ecu->getTempoSet());
}

void MainWindow::paintEvent(QPaintEvent*) // artificial leather..
{
    QPainter painter(this);
    QRect rect(0, 0, width(), height());
    painter.drawImage(rect, bg);
}

MainWindow::~MainWindow()
{
    data->writeData(ecu->getMileage(), ecu->getTrip());
    ecu->setThreadRunning(false);
    ecu->wait();
    // ecu and data cleaned up by Qt
    delete ui;
}





