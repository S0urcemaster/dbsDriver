#include "datamanagement.h"

DataManagement::DataManagement(QObject* parent) : QObject(parent)
{
}

void DataManagement::readData()
{
    QFile DataManager("data.txt", parent());
    if(QFile::exists("data.txt"))
    {
        DataManager.open(QIODevice::ReadOnly | QIODevice::Text);
        mileage = DataManager.readLine().toDouble();
        trip = DataManager.readLine().toDouble();
    }
    else
    {
        mileage = 203786.42; //Set value if file is not present
        trip = 220.74; //Set value if file is not present
    }
    DataManager.close();
}

void DataManagement::writeData(double mileage, double trip)
{
    QFile DataManager("data.txt", parent());
    DataManager.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&DataManager);
    out << mileage << "\n";
    out << trip << "\n";
    DataManager.close();
}

double DataManagement::getMileage()
{
    return mileage;
}

double DataManagement::getTrip()
{
    return trip;
}

DataManagement::~DataManagement()
{

}




