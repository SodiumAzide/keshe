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
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(125, 185, 222));
    QBrush brush(QColor(125, 185, 222)); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷
    painter.drawRect(0, 0, 200, 100); //绘制矩形
}

MainWindow::~MainWindow()
{
    delete ui;
}
