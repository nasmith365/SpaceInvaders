#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication clickableMapApp(argc, argv);
    MainWindow w;
    w.show();
    
    return clickableMapApp.exec();
}
