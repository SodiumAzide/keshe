#include "mainwindow.h"
#include <QApplication>
#include "thingadd.h"
#include <QMessageBox>
#include <QFile>

map<QString, vector<ll> > TagToThing;
QString DATA_FILE = "./data/data.txt";
QString Now_User;
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
    void addTag(QString tag){
        if(TagToThing.find(tag)!=TagToThing.end()){
            TagToThing[tag].push_back(Thing_num);
        }else{
            TagToThing[tag]=vector<ll> {Thing_num};
        }
        if(find(Tag.begin(), Tag.end(), tag)==Tag.end()){
            Tag.push_back(tag);
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
            //QString out;out.append(name_tmp);out.append(QString::number(money)); out.append(QString::number(New));
            //QMessageBox::warning(&_add_tmp, "a",out, QMessageBox::Yes);
        }
    }
    void removThing(){
        //wait to add data
        return;
    }
};

int main(int argc, char *argv[])
{
    //data define
    QApplication a(argc, argv);
    MainWindow w;
    MainData DATA;

    //exe
    w.setWindowTitle("你好");
    w.show();
    DATA.addThing();

    return a.exec();
}
