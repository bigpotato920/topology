#include <QDebug>
#include <QMessageBox>
#include "coordinate.h"

Coordinate::Coordinate(QObject *parent) :
    QObject(parent)
{
    coordinate_count = 0;
}


int Coordinate::getCount()
{
    return coordinate_count;
}

double Coordinate::getLat(int i)
{
    return latitudes[i];
}

double Coordinate::getLon(int i)
{
    return longitudes[i];
}

void Coordinate::getPointIndex(int index)
{
    qDebug() << "index = " << index;
    QMessageBox::about(NULL, "Point index", QString::number(index));
}

void Coordinate::increaseCount()
{
    coordinate_count++;
}

void Coordinate::setLon(int i, int lon)
{
    longitudes[i] = lon;
}

void Coordinate::setLat(int i, int lat)
{
    latitudes[i] = lat;
}
