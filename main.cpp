#include "topologydialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TopologyDialog w;
    w.show();
    
    return a.exec();
}
