#include "mainwindow.h"
#include <QApplication>
#include "thingadd.h"
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("你好");
    w.show();
    ThingAdd test;
    test.show();
    return a.exec();
}
