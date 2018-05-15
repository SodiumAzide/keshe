#include "thing.h"
#include "ui_thingadd.h"
#include "ui_my_thing_sou.h"
#include "ui_bug_it.h"
#include "ui_help.h"
#include <QMessageBox>
#include <QDialog>
#include <QBoxLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QPalette>
#include <QGraphicsDropShadowEffect>
#include <QTimeEdit>
#include <QDateTime>
#include <QString>

QString DATA_FILE = "./data.txt";
//////////////////color//////////////////////


//////////////////物品总数据//////////////////////////////
Thing::~Thing(){
    Save_data();
}
Thing::Thing(QString Now_){
    Load_data();
    Now_User = Now_;
    db = this;
    wait = 0;
}
void Thing::Save_data(){
    QFile fdata(DATA_FILE);
    fdata.open(QIODevice::WriteOnly|QIODevice::Text);
    fdata.write(QString::number(Num).toUtf8());
    fdata.write(QString("\n").toUtf8());
    QString bl = QString(" ");
    for(auto a:DATA){
        qDebug() << "Backuping   " << a.belonger;
        fdata.write((a.Thing_name.trimmed() + bl + a.belonger + bl).toUtf8());
        fdata.write((QString::number(a.money) + bl + QString::number(a.Thing_num) + bl + \
                     QString::number(a.start_time) + bl + QString::number(a.end_time) + bl + \
                     QString::number(a.now_money) + bl).toUtf8());
        fdata.write((a.describe.trimmed() + QString(".") + bl + a.buyer.trimmed()).toUtf8());
        qDebug() << (a.describe.trimmed() + QString(".") + bl + a.buyer.trimmed())<< "   Save data, describe";
        fdata.write("\n");
    }
    fdata.close();
}
void Thing::Load_data(){
    QFile fdata(DATA_FILE);
    QString tmp;
    things tmpp;
    if(!fdata.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "First time to use????";
        return;
    }
    Num = fdata.readLine().trimmed().toLongLong();
    while(!fdata.atEnd()){
        tmp = fdata.readLine();
        (tmpp.Thing_name = tmp.section(" ", 0, 0));
        (tmpp.belonger = tmp.section(" ", 1, 1));
        (tmpp.money = tmp.section(" ", 2, 2).toLongLong());
        (tmpp.Thing_num = tmp.section(" ", 3, 3).toLongLong());
        (tmpp.start_time = tmp.section(" ", 4, 4).toLongLong());
        (tmpp.end_time = tmp.section(" ", 5, 5).toInt());
        (tmpp.now_money = tmp.section(" ", 6, 6).toLongLong());
        tmpp.describe = tmp.section(" ", 7, 7);
        qDebug() << (tmpp.buyer = tmp.section(" ", 8, 8));
        tmpp.describe = tmpp.describe.left(tmpp.describe.length() - 1);
        DATA.push_back(tmpp);
    }
    qDebug() << "Finished loading data";
}
void Thing::addThing(){
    ThingAdd _add_tmp(0, Now_User);
    _add_tmp.ui->Delete_Thing->setEnabled(0);
    _add_tmp.setWindowTitle("物品信息");
    _add_tmp.ui->Start_Time->setMinimumDateTime(QDateTime::currentDateTime());
    if(_add_tmp.exec() == QDialog::Accepted){
        QString name_tmp=_add_tmp.Thing_name, des = _add_tmp.desctibe.replace(" ", "").replace("\n", "")\
                .replace("\r", "").replace("\t", "");
        ll money=_add_tmp.money, ttime=_add_tmp.time;
        qDebug() << Now_User << "  79";
        DATA.push_back(things(name_tmp, Now_User, money, Num, ttime, ttime + 5 * 60, des));
        wait = 1;
        Num++;
    }
}
QVBoxLayout* Thing::Show(QString User, bool OnlyMine, bool Not_finished){

    QVBoxLayout *ne = new QVBoxLayout();
    ll now_time = QDateTime::currentDateTime().toTime_t();
    ne->setSpacing(7);
    for(auto a:DATA){
        if(OnlyMine && a.belonger != Now_User)continue;
        if(Not_finished && now_time > a.end_time)continue;
        if(User == QString("")||User == a.belonger || QString(a.buyer).contains(User) || \
                a.Thing_name.contains(User, Qt::CaseInsensitive) || QString::number(a.Thing_num).contains(User) ||\
                a.describe.contains(User)){
            QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect;
            shadow_effect->setOffset(-4, 4);
            shadow_effect->setColor(Qt::gray);
            shadow_effect->setBlurRadius(8);
            My_Thing_Sou* one = new My_Thing_Sou(0, a.Thing_num, db, Now_User);
            one->setWindowFlags(Qt::FramelessWindowHint);
            one->setMinimumSize(560, 60);
            one->setGraphicsEffect(shadow_effect);
            ne->addWidget(one);
        }
    }
    ne->addStretch();
    return ne;
}
/////////////////////////////////////////////////////////////////////////
ThingAdd::ThingAdd(QWidget *parent, QString Now_U) :
    QDialog(parent),
    ui(new Ui::ThingAdd)
{
    Now_User = Now_U;
    setFixedSize(464, 286);
    ui->setupUi(this);
    ui->Thing_money->setMaxLength(10);
    ui->Thing_Name->setMaxLength(10);
}

ThingAdd::~ThingAdd()
{
    delete ui;
}

void ThingAdd::Thing_Edit(QString name, ll money, ll start_time, QString des){
    ui->Thing_Name->setText(name.trimmed());
    ui->Thing_money->setText(QString::number(money));
    //ui->Start_Time->setTime(QDateTime::fromTime_t(start_time));
    ui->Start_Time->setDateTime(QDateTime::fromTime_t(start_time));
    ui->textEdit->setText(des);
}

void ThingAdd::on_Thing_Confirm_clicked(){
    if(ui->Delete_Thing->isChecked()){
        accept();
        return;
    }
    bool ok=1;
    ui->Thing_money->text().toLongLong(&ok, 10);
    if(ui->Thing_money->text().trimmed() == ""||ui->Thing_Name->text().trimmed() == ""){//||ui->Thing_money->text().toInt()>100){
        QMessageBox::warning(this, tr("错误"), tr("所有空不得为空"), QMessageBox::Yes);
    }else if(!ok){
        QMessageBox::warning(this, tr("错误"), tr("价格必须为数字"), QMessageBox::Yes);
    }else{
        (Thing_name = ui->Thing_Name->text());
        (money = ui->Thing_money->text().toLongLong());
        //(New = ui->Thing_New->text().toInt());
        ui->Start_Time->setMinimumDateTime(QDateTime::currentDateTime());
        (time = ui->Start_Time->dateTime().toTime_t());
        desctibe = ui->textEdit->toPlainText();
        accept();
    }
}
///////////////////////////////////////////////////
My_Thing_Sou::My_Thing_Sou(QWidget *parent, ll num, Thing *datebase, QString Now_):
    QDialog(parent),
    ui(new Ui::My_Thing_Sou)
{
    db = datebase;
    Now_User = Now_;
    Num = num;
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(88, 178, 220)");
    Update(Num);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Myshow()));
    timer->start(2000);//refresh per 2 seconds
    Myshow();
}

My_Thing_Sou::~My_Thing_Sou(){
    delete ui;
}
void My_Thing_Sou::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        Bug_it *tmpp = new Bug_it(0, db, Now_User);
        tmpp->Update(Num);
        tmpp->exec();
        delete tmpp;
    }
}
void My_Thing_Sou::Update(ll num){
    ll money;QString name;
    for(auto &tmpp : (db->DATA)){
        if(tmpp.Thing_num == num){
            start_time = tmpp.start_time, now_money = tmpp.now_money, stop_time = tmpp.end_time;money=tmpp.money;
            name = tmpp.Thing_name;buyer = tmpp.buyer;
            break;
        }
    }
    ui->Thing_Name->setText(QString("名称:") + name.trimmed());
    ui->Thing_Num->setText(QString("编号:") + QString::number(num));
    ui->Time->setText(QString("开始时间:") + (QDateTime::fromTime_t(start_time)).toString("yyyy-MM-dd hh:mm"));
    ui->Start_Money->setText((QString("起拍价格:") + QString::number(money)));
    ui->Now_Money->setText((QString("当前价格:") + QString::number(now_money)));
}
void My_Thing_Sou::Myshow()
{
    Update(Num);
    ll now_time = QDateTime::currentDateTime().toTime_t();
    if(now_time<start_time){
        ui->Status->setText(QString("Pending"));
        ui->Status->setStyleSheet("font: 11pt \"Arial\";font: rgb(158, 121, 4)");
    }else if(now_time < stop_time){
        ui->Status->setText(QString("Running"));
        ui->Status->setStyleSheet("font: 11pt \"Arial\";font: rgb(46, 226, 109)");
    }else{
        //qDebug() << now_time << " " << stop_time << " 226";
        if(ui->Status->text().trimmed() == "Running"){
            if(buyer.trimmed() != QString(""))
                db->Inform = QString("商品%1以%2元被%3成功拍下").arg(ui->Thing_Name->text().trimmed()).arg(now_money).arg(buyer);
            else
                db->Inform = QString("商品%1流拍").arg(ui->Thing_Name->text().trimmed());
        }
        ui->Status->setText(QString("End"));
        ui->Status->setStyleSheet("font: 11pt \"Arial\";font: rgb(106, 14, 36)");

    }
}

/////////////////the final class/////////////////////

Bug_it::Bug_it(QWidget *parent, Thing *datebase, QString Now_) :
    QDialog(parent),
    ui(new Ui::Bug_it)
{
    setFixedSize(455, 326);
    Now_User = Now_;
    ui->setupUi(this);
    ui->Add_Price->setMaxLength(12);
    db = datebase;
    ui->lcdNumber->setDigitCount(7);
    QTimer * sec = new QTimer;
    connect(sec, SIGNAL(timeout()), this, SLOT(data_update()));
    sec->start(1000);
}
Bug_it::~Bug_it(){
    delete ui;
    for(auto &tmpp : (db->DATA)){
        if(tmpp.Thing_num == _num){
            //qDebug() << "changing";
            tmpp.now_money = now_money;tmpp.end_time=stop_time;
            break;
        }
    }
}
void Bug_it::data_update(){
    Update(_num);
    ll now_time = QDateTime::currentDateTime().toTime_t();
    if(start_time < now_time || Now_User!=belonger){
        //qDebug() << Now_User << "  " << belonger;
        ui->Data_Edit->setEnabled(0);
    }
    if(Now_User == belonger){
        ui->Add_Price->setEnabled(0);
        ui->HigerPrice->setEnabled(0);
    }
    if(changable || start_time > now_time)
        ui->HigerPrice->setEnabled(Now_User!=belonger);
    if(now_time < start_time){
        //qDebug() << now_time << " " << start_time << " test";
        ui->Time_Status->setText("距离开始还有");
        ll rest = start_time - now_time;
        ui->lcdNumber->display(ll_to_time(rest));
        ui->Add_Price->setEnabled(0);
    }else if(now_time < stop_time){
        ui->Time_Status->setText("距离结束还有");
        ui->lcdNumber->display(ll_to_time(stop_time - now_time));
    }else{
        //qDebug() << now_time << " " << stop_time;
        ui->Time_Status->setText("已结束");
        ui->lcdNumber->display("0:0:0");
        ui->Add_Price->setEnabled(0);
        ui->HigerPrice->setEnabled(0);
    }
    ui->Now_Money->setText(QString("当前价格:") + QString::number(now_money));
}
QString Bug_it::ll_to_time(ll times){
    ll sec = times%60;
    ll minu = times/60%60;
    ll hour = times/3600;
    QString tmp = QString("%1:%2:%3").arg(hour).arg(minu).arg(sec);
    return tmp;
}
void Bug_it::Update(ll num){
    _num = num;
    for(auto tmp : db->DATA){
        if(tmp.Thing_num == num){
            now_money = tmp.now_money;stop_time = tmp.end_time;now_money=tmp.now_money;_num = tmp.Thing_num;
            start_time = tmp.start_time;belonger = tmp.belonger;describe=tmp.describe;Thing_name=tmp.Thing_name;
            //qDebug() << tmp.belonger << "  " << belonger << "    debug";
            ui->Thing_Name->setText(QString("物品名称:") + tmp.Thing_name);
            ui->Start_Money->setText(QString("起步价:") + QString::number(tmp.money));
            ui->payer->setText(QString("出价人:") + tmp.buyer.trimmed());
            ui->textBrowser->setPlainText(describe);
            //ui->Buyer->setText(buyer);
            break;
        }
    }
}

void Bug_it::on_HigerPrice_clicked(){
    bool ok=0;
    ll add = ui->Add_Price->text().toLongLong(&ok);
    if(ui->Add_Price->text().isEmpty() || !ok){
        QMessageBox::warning(this, "错误", "请检查输入", QMessageBox::Yes);
        return;
    }
    for(auto &tmp : db->DATA){
        if(tmp.Thing_num == _num){
            tmp.now_money += add;
            //qDebug() << tmp.now_money << "  Now money";
            tmp.buyer = Now_User;
            tmp.end_time = QDateTime::currentDateTime().currentDateTime().toTime_t() + 5 * 60;//delate for 5 min
            ui->Add_Price->clear();
            db->Inform = QString("用户:%1 在商品%2出价%3元").arg(Now_User).arg(tmp.Thing_name).arg(tmp.now_money);
            break;
        }
    }
}
void Bug_it::on_Data_Edit_clicked(){
    this->close();
    ThingAdd *tmp = new ThingAdd;
    //tmp->setFixedSize(455, 326);
    tmp->Thing_Edit(Thing_name, start_money, start_time, describe);
    if(tmp->exec()==QDialog::Accepted){
        if(tmp->ui->Delete_Thing->isChecked()){
            for(unsigned i=0; i<db->DATA.size(); i++){
                if(db->DATA[i].Thing_num == _num){
                    db->DATA.erase(db->DATA.begin() + i);
                    db->wait = 1;
                    break;
                }
            }
        }else{
            for(auto &tmpp : (db->DATA)){
                if(tmpp.Thing_num == _num){
                    //qDebug() << "Save";
                    tmpp.money=tmp->money,tmpp.now_money=tmp->money;
                    tmpp.start_time=tmp->time,tmpp.Thing_name=tmp->Thing_name;tmpp.end_time = tmp->time + 5 * 60;
                    tmpp.describe=tmp->ui->textEdit->toPlainText().replace("\n", "").replace("\r", "").replace("\t", "");
                    //qDebug() << tmpp.end_time << "   end time";
                    break;
                }
            }
        }
    }
}
/////////////////////////////////////////////////////////
help::help(QWidget *parent):
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    ui->OpenSou->setOpenExternalLinks(true);
    ui->OpenSou->setText(tr("<a href=\"https://github.com/SodiumAzide/keshe\">开源地址"));
    ui->Blog->setOpenExternalLinks(true);
    ui->Blog->setText(tr("<a href=\"https://www.zhihu.com/people/ankikong/\">Blog"));
    //QImage *logo_img = new QImage(":/new/icon/icon.png");
    //QImage *scaled_logo_img = new QImage();
    //*scaled_logo_img=logo_img->scaled(180,180,Qt::KeepAspectRatio);
    //ui->label_2->setPixmap(QPixmap::fromImage(*scaled_logo_img));
}
help::~help(){
    delete ui;
}/*
void help::paintEvent(QPaintEvent *)
{
QPainter painter(this);
QPixmap pix;
pix.load(":/new/icon/icon.png");
painter.drawPixmap(0,0,100,100,pix);

    qreal width = pix.width(); //获得以前图片的宽和高
    qreal height = pix.height();

    pix = pix.scaled(width*2,height*2,Qt::KeepAspectRatio);
    //将图片的宽和高都扩大两倍，并且在给定的矩形内保持宽高的比值
    painter.drawPixmap(100,100,pix);
}*/
