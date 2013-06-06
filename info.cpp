#include <QDebug>
#include <QMessageBox>
#include "info.h"

Info::Info(QObject *parent) :
    QObject(parent)
{
    count = 0;
}

int Info::getCount()
{
    return count;
}

double Info::getLat(int i)
{
    return lats[i];
}

double Info::getLon(int i)
{
    return lons[i];
}

int Info::getDst(int src)
{
    return edges[src];
}

void Info::showPointIndex(int index)
{
    qDebug() << "index = " << index;
    QMessageBox::about(NULL, "Point index", QString::number(index));
}

void Info::setPos(long lon, long lat) {
    lons[count] = lon;
    lats[count] = lat;
    count++;
}

void Info::setEdge(int src, int dst)
{
    edges[src] = dst;
}
