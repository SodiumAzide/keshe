#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent, Thing *data, Login *secu) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    security = secu;
    a=data;
    setFixedSize(1000, 636);
    ui->setupUi(this);
    QTimer *tmer = new QTimer;
    connect(tmer, SIGNAL(timeout()), this, SLOT(datachange()));
    //QWidget *aa = new QWidget;
    //aa->setLayout(a->Show("", 0, 0));
    //ui->All_Thing->setWidget(aa);
    a->wait = 1;
    datachange();
    tmer->start(2000);
}
void MainWindow::datachange(){
    if(a->wait){
        QWidget *aa = new QWidget;
        ll cal[20];
        aa->setLayout(a->Show("", 0, 0, cal));
        QString cal_data = QString("共查到:%1件;未开始:%2件;进行中:%3件;已结束:%4;成功:%5件;成交金额:%6;失败:%7件").arg(cal[0]).arg(cal[1])\
                .arg(cal[2]).arg(cal[3]).arg(cal[5]).arg(cal[7]).arg(cal[4]);
        ui->Caculate->setText(cal_data);
        ui->All_Thing->setWidget(aa);
        a->wait = 0;
        //delete cal;
    }
    if(a->Inform != QString("")){
        QString tmp = "%1 %2";
        tmp = tmp.arg(QTime::currentTime().toString("hh:mm")).arg(a->Inform.trimmed());
        qDebug()  << tmp << "   Event";
        ui->History->append(tmp);
        a->Inform = "";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete a;
}

void MainWindow::on_Search_clicked(){
    QString keyword = ui->lineEdit->text().trimmed();
    QWidget *aa = new QWidget;
    ll cal[20];
    aa->setLayout(a->Show(keyword, ui->Just_Show_Mine->isChecked(), ui->NotFinished->isChecked(), cal));
    ui->All_Thing->setWidget(aa);
    QString cal_data = QString("共查到:%1件;未开始:%2件;进行中:%3件;已结束:%4;成功:%5件;成交金额:%6;失败:%7件").arg(cal[0]).arg(cal[1])\
            .arg(cal[2]).arg(cal[3]).arg(cal[5]).arg(cal[7]).arg(cal[4]);
    ui->Caculate->setText(cal_data);
    //delete cal;
}
void MainWindow::on_Help_clicked(){
    help *he = new help;
    he->show();
}
void MainWindow::on_Security_clicked(){
    ChangePass *ccc = new ChangePass(0, security);
    ccc->show();
}
void MainWindow::on_Add_Thing_clicked(){
    a->addThing();
}
