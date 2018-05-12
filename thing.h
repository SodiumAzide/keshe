#ifndef THINGADD_H
#define THINGADD_H

#include <QDialog>
#ifndef STDAFX_H
#include "stdafx.h"
#endif
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QMouseEvent>
#include <QPalette>
namespace Ui {
class ThingAdd;
class Thing_Tag_Select;
class My_Thing;
class My_Thing_Sou;
}
/////////////数据存储/////////////////
class Thing{
public:
    ll Num=1;
    struct things
    {
        things(QString Tname, int H_new, QString user, ll Money, ll Thing_n) {
            Thing_name = Tname;
            How_new = H_new;
            belonger = user;
            money=Money;
            Thing_num = Thing_n;
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
        QString Thing_name, belonger;
        vector<QString> Tag;
        int How_new;
        ll Thing_num, money, now_money;

    };
    void addThing();
    vector<things> DATA;
    void Save_data();

private:

};
//////////物品增添和删除界面/////////////////
class ThingAdd : public QDialog
{
    Q_OBJECT

public:
    explicit ThingAdd(QWidget *parent = 0);
    ~ThingAdd();
    QString Thing_name;
    ll money;
    int New;
    vector<QCheckBox*> Tag_Select;
    vector<int>Tag;

private:
    Ui::ThingAdd *ui;
private slots:
    void on_Thing_Confirm_clicked();
};

////////////标签处理界面///////////////////
class Thing_Tag_Select : public QWidget {
    Q_OBJECT
public:
    explicit Thing_Tag_Select(QWidget *parent = 0);
    ~Thing_Tag_Select();
    vector<QCheckBox*> initWidget(vector<QString> Tag_Sum);
private:

};
/////////////单个物品窗口///////////////
class My_Thing_Sou : public QDialog
{
    Q_OBJECT

public:
    QString User;
    explicit My_Thing_Sou(QWidget *parent = 0);
    ~My_Thing_Sou();
private:
    Ui::My_Thing_Sou *ui;

protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *);
};
/////////////总物品窗口////////////////
class My_Thing : public QDialog
{
    Q_OBJECT

public:
    explicit My_Thing(QWidget *parent = 0);
    ~My_Thing();
private:
    Ui::My_Thing *ui;
protected:
    void init_list();

};

#endif // THINGADD_H
