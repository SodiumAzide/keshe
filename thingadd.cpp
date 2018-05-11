#include "thingadd.h"
#include "ui_thingadd.h"
#include <QMessageBox>
#include <QDialog>
#include <QBoxLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDebug>
extern vector<QString> Tag_Sum;

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

        for(int i=0; i<Tag_Select.size(); i++){
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
