#include <QApplication>
#include <QMessageBox>
#include <QFile>

#include "mainwindow.h"
#ifndef THING_H
#include "thing.h"
#endif
#include "login.h"
#ifndef STDAFX_H
#include "stdafx.h"
#endif


extern QString Now_User;
extern vector<QString> Tag_Sum;

int main(int argc, char *argv[])
{
    //data define
    QApplication a(argc, argv);
    MainWindow w;
    Login aa;

    //exe
    w.setWindowTitle("你好");
    w.show();
    aa.show();

    return a.exec();
}
