#include <QWidget>
#include <QWebFrame>
#include <QWebView>
#include <QWebPage>
#include <QWebSecurityOrigin>

#include "toplogydialog.h"
#include "ui_toplogydialog.h"
#include "coordinate.h"

ToplogyDialog::ToplogyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToplogyDialog)
{
    ui->setupUi(this);
    m_coordinate = new Coordinate(this);
    initMap();
    test();
}

ToplogyDialog::~ToplogyDialog()
{
    delete ui;
}


void ToplogyDialog::test()
{

    refreshMap(116.391596, 39.905841);
    refreshMap(108.979783, 34.257154);
    refreshMap(113.328695, 23.131285);
    refreshMap(91.122236, 29.642912);
}

void ToplogyDialog::initMap()
{
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavaEnabled, true);
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addJavaScriptObject()));
}

void ToplogyDialog::addPoint(double lon, double lat)
{
    int count = m_coordinate->getCount();
    m_coordinate->setLon(count, lon);
    m_coordinate->setLat(count, lat);
    m_coordinate->increaseCount();
}
void ToplogyDialog::refreshMap(double lon, double lat)
{

    addPoint(lon, lat);
    ui->webView->load(QUrl("qrc:/final.html"));
    ui->webView->show();
}

void ToplogyDialog::addJavaScriptObject()
{

    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("Coordinate",m_coordinate);
}
