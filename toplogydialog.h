#ifndef TOPLOGYDIALOG_H
#define TOPLOGYDIALOG_H

#include <QDialog>

class Coordinate;

namespace Ui {
class ToplogyDialog;
}

class ToplogyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ToplogyDialog(QWidget *parent = 0);
    ~ToplogyDialog();
private slots:
    void addJavaScriptObject();
    void test();
    
private:
    void initServerService();
    void initMap();
    void addPoint(double lon, double lat);
    void refreshMap(double longitude, double latitude);
    Ui::ToplogyDialog *ui;
    Coordinate *m_coordinate;
};

#endif // TOPLOGYDIALOG_H
