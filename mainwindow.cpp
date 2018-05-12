#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    setFixedSize(1000, 618);
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}
