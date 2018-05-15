#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QWidget>

#include "mainwindow.h"
#ifndef THING_H
#include "thing.h"
#endif
#ifndef LOGIN_H
#include "login.h"
#endif
#ifndef STDAFX_H
#include "stdafx.h"
#endif



int main(int argc, char *argv[])
{
    //data define
    QApplication a(argc, argv);

    Login aa;


    //exe

    if(aa.exec() != QDialog::Accepted){
        return 0;
    }
    Thing *data = new Thing(aa.Now_User);

    MainWindow w(0, data, &aa);
    w.setFixedSize(1000, 618);
    w.setWindowTitle("kong的竞拍系统");
    w.show();
    return a.exec();
}
