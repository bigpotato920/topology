#ifndef COORDINATE_H
#define COORDINATE_H

#include <QObject>

class Coordinate : public QObject
{
    Q_OBJECT
public:
    explicit Coordinate(QObject *parent = 0);
    void increaseCount();
    void setLon(int i, int lon);
    void setLat(int i, int lat);

public slots:

    int getCount();
    double getLat(int i);
    double getLon(int i);

    void getPointIndex(int index);

private:
    enum {MAX_COORDINATE_NUM = 20 };
    double latitudes[MAX_COORDINATE_NUM];
    double longitudes[MAX_COORDINATE_NUM];
    int coordinate_count;
};

#endif // COORDINATE_H
