#include "thingadd.h"
#include "ui_thingadd.h"
#include <QMessageBox>

ThingAdd::ThingAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThingAdd)
{
    setFixedSize(400, 247);
    setWindowTitle("物品信息");
    ui->setupUi(this);
}

ThingAdd::~ThingAdd()
{
    delete ui;
}

void ThingAdd::on_Thing_Confirm_clicked(){
    if(ui->Thing_money->text().trimmed() == ""||ui->Thing_Name->text().trimmed() == ""|| ui->Thing_New->text().trimmed() == ""){
        QMessageBox::warning(this, tr("错误"), tr("所有空不得为空"), QMessageBox::Yes);
    }else{
        accept();
    }
}
