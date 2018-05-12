#include "thing.h"
#include "ui_thingadd.h"
#include "ui_my_thing.h"
#include "ui_my_thing_sou.h"
#include <QMessageBox>
#include <QDialog>
#include <QBoxLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QPainter>
extern vector<QString> Tag_Sum;
extern QString fdata;
extern QString Now_User;

//////////////////物品总数据//////////////////////////////
void Thing::Save_data(){
    QFile fdata(DATA_FILE);
    fdata.open(QIODevice::WriteOnly|QIODevice::Text);

    for(auto a:DATA){
        int Tag_num = a.Tag.size();
        fdata.write((a.Thing_name + " " + a.belonger + " " + QString::number(Tag_num) + " ").toUtf8());
        for(auto _tmp:a.Tag){
            fdata.write((_tmp + " ").toUtf8());
        }
    }
    fdata.close();
}
void Thing::addThing(){
    ThingAdd _add_tmp;
    _add_tmp.setWindowTitle("物品信息");
    if(_add_tmp.exec() == QDialog::Accepted){
        QString name_tmp=_add_tmp.Thing_name;
        ll money=_add_tmp.money;
        int New=_add_tmp.New;
        DATA.push_back(things(name_tmp, New, Now_User, money, Num));
        (DATA.end()-1)->addTag(_add_tmp.Tag);
    }
}
/////////////////////////////////////////////////////////////////////////
ThingAdd::ThingAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThingAdd)
{
    setFixedSize(400, 247);
    ui->setupUi(this);
    Thing_Tag_Select *a = new Thing_Tag_Select;
    Tag_Select=a->initWidget(Tag_Sum);
    ui->Thing_Tag_Select->setWidget(a);
}

ThingAdd::~ThingAdd()
{
    delete ui;
}

void ThingAdd::on_Thing_Confirm_clicked(){
    if(ui->Thing_money->text().trimmed() == ""||ui->Thing_Name->text().trimmed() == ""|| \
            ui->Thing_New->text().trimmed() == ""){//||ui->Thing_money->text().toInt()>100){
        QMessageBox::warning(this, tr("错误"), tr("所有空不得为空"), QMessageBox::Yes);
    }else{
        Thing_name = ui->Thing_Name->text();
        money = ui->Thing_money->text().toLongLong();
        New = ui->Thing_New->text().toInt();

        for(unsigned i=0; i<Tag_Select.size(); i++){
            if(Tag_Select[i]->checkState()){
                Tag.push_back(i);
            }
        }
        accept();
    }
}

Thing_Tag_Select::Thing_Tag_Select(QWidget *parent) : QWidget(parent){

}
Thing_Tag_Select::~Thing_Tag_Select(){

}

vector<QCheckBox*> Thing_Tag_Select::initWidget(vector<QString> Tag_Sum){
    QVBoxLayout* lay = new QVBoxLayout(this);
    auto whole = new vector<QCheckBox*>;
    for(auto tmp:Tag_Sum){
    //for(int i=0; i<20; i++){
        QCheckBox* check = new QCheckBox(tmp, this);
        check->setMinimumSize(check->size());
        lay->addWidget(check);
        (*whole).push_back(check);

    }
    this->setLayout(lay);
    return *whole;
}
///////////////////////////////////////////////////
My_Thing_Sou::My_Thing_Sou(QWidget *parent):
    QDialog(parent),
    ui(new Ui::My_Thing_Sou)
{
    ui->setupUi(this);

}
void  My_Thing_Sou::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QBrush brush(QColor(125, 185, 222)); //画刷
    painter.setBrush(brush); //添加画刷
    painter.drawRect(0, 0, this->size().height(), this->size().width()); //绘制矩形
}
My_Thing_Sou::~My_Thing_Sou(){
    delete ui;
}
void My_Thing_Sou::mouseReleaseEvent(QMouseEvent *event)
{

}
///////////////////////////////////////////////////
My_Thing::My_Thing(QWidget *parent):
    QDialog(parent),
    ui(new Ui::My_Thing)
{
    ui->setupUi(this);


}
My_Thing::~My_Thing(){

}
void My_Thing::init_list(){
    QVBoxLayout *n = new QVBoxLayout(this);
    if()
}
