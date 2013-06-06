#include <QWidget>
#include <QWebFrame>
#include <QWebView>
#include <QWebPage>
#include <QWebSecurityOrigin>
#include <QUdpSocket>
#include <QDebug>
#include <QTimer>

#include "topologydialog.h"
#include "ui_topologydialog.h"
#include "info.h"

TopologyDialog::TopologyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopologyDialog)
{
    ui->setupUi(this);

    info = new Info(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(9996);
    timer = new QTimer(this);
    timer->start(5*1000);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getEdgeInfo()));
    connect(timer, SIGNAL(timeout()), this, SLOT(requestEdgeInfo()));
    initMap();
    initAddressList();
    test();

}

TopologyDialog::~TopologyDialog()
{
    delete ui;
}


void TopologyDialog::test()
{

    info->setPos(91.122236, 29.642912);
    info->setPos(102.742145, 24.998378);
    info->setPos(113.328695, 23.131285);
    info->setPos(108.979783, 34.257154);

    addToGraph("10.0.0.2", "10.0.0.4");
    addToGraph("10.0.0.3", "10.0.0.4");
    addToGraph("10.0.0.4", "10.0.0.5");

    refreshMap();
}

void TopologyDialog::requestEdgeInfo()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    const char *signal = "route";
    out.writeRawData(signal, strlen(signal));

    //udpSocket->writeDatagram(datagram, datagram.size(), QHostAddress("11.0.0.34"), 9999);
    //udpSocket->writeDatagram(datagram, datagram.size(), QHostAddress("10.0.0.60"), 9999);
    udpSocket->writeDatagram(datagram, datagram.size(), QHostAddress("192.168.137.149"), 9999);

}

void TopologyDialog::getEdgeInfo()
{
    qDebug() << "get edge info";
    QByteArray datagram;
    QHostAddress address;

    QDataStream in(&datagram, QIODevice::ReadOnly);
    char msgRecv[256];
    char dstIp[256];
    char nextHop[256];
    int nread = 0;
    int count;

    do {
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &address);

    } while(udpSocket->hasPendingDatagrams());
    nread = in.readRawData(msgRecv, 256);
    if (nread > 0) {
        msgRecv[nread ] = '\0';
        qDebug() << QString(msgRecv) << address.toString();
        count = getEdgeCount(msgRecv);
        for (int i = 0; i < count; i++) {
            sscanf(msgRecv + i*16, "%8s%8s", dstIp, nextHop);
            convertIp(dstIp);
            convertIp(nextHop);
            qDebug() << "dstIp:" << dstIp << "nextHop:" << nextHop;
            if (QString(nextHop) == "0.0.0.0") {
                addToGraph(address.toString(), dstIp);
            } else {
                addToGraph(address.toString(), nextHop);
            }

        }
    }
}


void TopologyDialog::addToGraph(QString srcIp, QString nextHop)
{
    if (ipDict.contains(srcIp) && ipDict.contains(nextHop))
        info->setEdge(ipDict[srcIp], ipDict[nextHop]);
}

void TopologyDialog::convertIp(char *ip) {
    int a, b, c, d;
    sscanf(ip, "%2x%2x%2x%2x", &a, &b, &c, &d);
    sprintf(ip, "%d.%d.%d.%d", d, c, b, a);
}

int TopologyDialog::getEdgeCount(char *edges) {
    return strlen(edges) / 16;
}

void TopologyDialog::initMap()
{
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavaEnabled, true);
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addJavaScriptObject()));
}

void TopologyDialog::initAddressList()
{

    addressList.append("10.0.0.2");
    addressList.append("10.0.0.3");
    addressList.append("10.0.0.4");
    addressList.append("10.0.0.5");

    for (int i = 0; i < addressList.size(); i++) {
        ipDict[addressList[i]] = i;
    }

}

void TopologyDialog::refreshMap()
{
    ui->webView->load(QUrl("qrc:/final.html"));
    ui->webView->show();
}

void TopologyDialog::addJavaScriptObject()
{

    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("info",info);
}

