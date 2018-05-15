#ifndef THINGADD_H
#define THINGADD_H

#include <QDialog>
#ifndef STDAFX_H
#include "stdafx.h"
#endif
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QMouseEvent>
#include <QPalette>
#include <QDebug>
extern vector<QString> Tag_Sum;
namespace Ui {
class ThingAdd; //增加物品时调用的窗口
class My_Thing_Sou; // 在主窗口对当个元素数据显示时调用
class Bug_it; // 竞拍窗口
class help;
}
/////////////数据存储/////////////////
class Thing {

public:
    ll Num=1;
    struct things
    {
        things(QString Tname=QString(""), QString user=QString(""), ll Money=0, ll Thing_n=0, ll timme=0, ll endt=0, QString des="") {
            Thing_name = Tname;
            belonger = user;
            money=Money;
            Thing_num = Thing_n;
            start_time = timme;
            end_time = endt;
            now_money = Money;
            describe = des;
        }
        QString Thing_name, belonger, buyer, describe;
        ll Thing_num, money, now_money, start_time, end_time;
        bool is_end;

    };
    ~Thing();
    Thing(QString Now_);
    void addThing();
    vector<things> DATA;
    void Save_data();
    void Load_data();
    QVBoxLayout* Show(QString User, bool OnlyMine, bool Not_finished);//search in the meantime
    QString Now_User;
    QTimer *minu, *seco;
    QString Inform="";
    bool wait = 0;


private:
    Thing *db;

};
//////////物品增添和删除界面/////////////////
class ThingAdd : public QDialog
{
    Q_OBJECT

public:
    explicit ThingAdd(QWidget *parent = 0, QString Now_U = "");
    ~ThingAdd();
    void Thing_Edit(QString name, ll money, ll start_time, QString des);
    QString Thing_name, Now_User, desctibe;
    ll money;
    int New;
    ll time;
    //vector<QCheckBox*> Tag_Select;
    //vector<int>Tag;
    Ui::ThingAdd *ui;

private:


private slots:
    void on_Thing_Confirm_clicked();
};

////////////标签处理界面///////////////////
/// \brief The Thing_Tag_Select class
/*
class Thing_Tag_Select : public QWidget {
    Q_OBJECT
public:
    explicit Thing_Tag_Select(QWidget *parent = 0);
    ~Thing_Tag_Select();
    vector<QCheckBox*> initWidget(vector<QString> Tag_Sum);
private:

};*/
/////////////单个物品窗口///////////////
class My_Thing_Sou : public QDialog
{
    Q_OBJECT

public:
    QString User, buyer;
    ll now_money, start_time, stop_time, Num;
    explicit My_Thing_Sou(QWidget *parent = 0, ll num=0, Thing *datebase=0, QString Now_="");
    ~My_Thing_Sou();
    void Update(ll num);
private:
    Ui::My_Thing_Sou *ui;
    QString _name, Now_User;
    ll _money, _time, _num, _now_mon;
    int _new;
    Thing *db;
private slots:
    void Myshow();

protected:
    void mouseReleaseEvent(QMouseEvent* event);
    //void paintEvent(QPaintEvent *);
};
//////////////the final class///////////////////////////
class Bug_it : public QDialog
{
    Q_OBJECT
public:
    ll add_money, now_money, start_time, stop_time, start_money, _num;
    QString Thing_name, Now_User, belonger, buyer, describe;
    bool changable;
    Thing *db;
    Bug_it(QWidget *parent=0, Thing *datebase=0, QString Now_="");
    ~Bug_it();
    void Update(ll num);
protected:
    Ui::Bug_it *ui;
private  slots:
    void on_HigerPrice_clicked();
    void on_Data_Edit_clicked();
    void data_update();
    QString ll_to_time(ll times);
};
/////////////////really final class/////////////////////////
class help : public QDialog
{
    Q_OBJECT
public:
    help(QWidget * parent = 0);
    ~help();
private:
    //void paintEvent(QPaintEvent *);

protected:
    Ui::help *ui;

};
#endif // THINGADD_H
