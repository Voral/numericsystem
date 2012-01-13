#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifndef Q_OS_MAC
    a.setWindowIcon(QPixmap(":/ico/icon.png"));
#endif
    a.setApplicationVersion("1.0");
    a.setApplicationName("Simulator \"Number system\"");
    QTranslator appTranslator;
    appTranslator.load("basetest_" + QLocale::system().name().left(2),":/trans");
    a.installTranslator(&appTranslator);
    MainWindow w;
    w.show();
    
    return a.exec();
}
