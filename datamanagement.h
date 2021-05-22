#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QFile>
#include <QTextStream>

/**
 * @brief The DataManagement class
 * Save mileage and trip km.
 */
class DataManagement : public QObject
{
    Q_OBJECT

    QFile DataManager;

    double mileage{};
    double trip{};

public:
    DataManagement(QObject* parent);

    /**
     * @brief readData
     * Read mileage and trip from file
     * @param parent
     */
    void readData();

    /**
     * @brief writeData
     * Write mileage and trip to file
     * @param parent
     * @param mileage
     * @param trip
     */
    void writeData(double mileage, double trip);

    double getMileage();

    double getTrip();

    ~DataManagement();
};

#endif // DATAMANAGEMENT_H
