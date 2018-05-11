#include <QApplication>
#include <QMessageBox>
#include <QFile>

#include "mainwindow.h"
#include "thingadd.h"
#include "login.h"
#ifndef STDAFX_H
#include "stdafx.h"
#endif

map<QString, vector<ll> > TagToThing;
QString DATA_FILE = "./data/data.txt";

extern QString Now_User;
extern vector<QString> Tag_Sum;

class Thing{
public:
    QString Thing_name, belonger;
    vector<QString> Tag;
    int How_new;
    ll Thing_num, money;
    Thing(QString Tname, int H_new, QString user, ll Money){
        Thing_name = Tname;
        How_new = H_new;
        belonger = user;
        money=Money;
    }
    void Save_data(){
        int Tag_num = Tag.size();
        QFile fdata(DATA_FILE);
        fdata.open(QIODevice::WriteOnly|QIODevice::Text);
        //data fomation:
        //Thing_name Thing_Belonger Thing_Tag_Num Thing_Tag
        fdata.write((Thing_name + " " + belonger + " " + QString::number(Tag_num) + " ").toUtf8());
        for(auto _tmp:Tag){
            fdata.write((_tmp + " ").toUtf8());
        }
        fdata.close();
    }
    void show(){
        return ;
    }
    void addTag(vector<int> &tmp){
        for(auto i:tmp){
            QString tag = Tag_Sum[i];
            if(TagToThing.find(tag)!=TagToThing.end()){
                TagToThing[tag].push_back(Thing_num);
            }else{
                TagToThing[tag]=vector<ll> {Thing_num};
            }
            if(find(Tag.begin(), Tag.end(), tag)==Tag.end()){
                Tag.push_back(tag);
            }
        }

    }
private:
    void text(){
    }
};
class MainData{
public:
    ll Num=1;
    vector<Thing> DATA;
    void addThing(){
        ThingAdd _add_tmp;
        _add_tmp.setWindowTitle("物品信息");
        if(_add_tmp.exec() == QDialog::Accepted){
            QString name_tmp=_add_tmp.Thing_name;
            ll money=_add_tmp.money;
            int New=_add_tmp.New;
            DATA.push_back(Thing(name_tmp, New, Now_User, money));
            (DATA.end()-1)->addTag(_add_tmp.Tag);
        }
    }
    void removThing(){
        //wait to add data
        return;
    }
private:

};

int main(int argc, char *argv[])
{
    //data define
    QApplication a(argc, argv);
    MainWindow w;
    MainData DATA;
    Login aa;

    //exe
    w.setWindowTitle("你好");
    w.show();
    aa.show();

    return a.exec();
}
