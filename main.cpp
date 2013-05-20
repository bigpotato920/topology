#include "toplogydialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToplogyDialog w;
    w.show();
    
    return a.exec();
}
