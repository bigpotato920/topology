#ifndef TOPOLOGYDIALOG_H
#define TOPOLOGYDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVector>

class Info;
class QUdpSocket;
class QTimer;


namespace Ui {
class TopologyDialog;
}

class TopologyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TopologyDialog(QWidget *parent = 0);

    ~TopologyDialog();
private slots:
    void getEdgeInfo();
    void addJavaScriptObject();
    void requestEdgeInfo();
    void test();
    
private:


    void initDict();
    void initMap();
    void initAddressList();
    void addPoint(double lon, double lat);
    void refreshMap();

    int getEdgeCount(char *edes);
    void convertIp(char *ip);
    void constructTopology();
    void addToGraph(QString srcIp, QString nextHop);

    Ui::TopologyDialog *ui;
    Info *info;
    QUdpSocket *udpSocket;
    QTimer *timer;
    QVector<QString> addressList;
    QMap<QString, int> ipDict;

};

#endif // TopologyDialog_H
