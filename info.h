#ifndef COORDINATE_H
#define COORDINATE_H

#include <QObject>

class Info : public QObject
{
    Q_OBJECT
public:
    explicit Info(QObject *parent = 0);
    void setPos(long lon, long lat);
    void setEdge(int src, int dst);


public slots:

    int getCount();
    double getLat(int i);
    double getLon(int i);
    int getDst(int src);
    void showPointIndex(int index);


private:



    enum {MAX_EDGE_NUM = 20 };
    double lats[MAX_EDGE_NUM];
    double lons[MAX_EDGE_NUM];
    int edges[MAX_EDGE_NUM];
    int count;
};

#endif // COORDINATE_H
