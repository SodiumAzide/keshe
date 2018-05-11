#include "login.h"
#include "ui_login.h"
#include "ui_new_account_ui.h"
#include <QMessageBox>
#include <QCryptographicHash>
extern QString Now_User;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    setFixedSize(400, 247);
    setWindowTitle(tr("登陆"));
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
void Login::on_New_Account_clicked() {
    New_Account_ui a;
    a.data = this;
    a.exec();
}
void Login::on_Login_Bot_clicked(){
    QString acc = ui->Account->text().trimmed(), pass = ui->Password->text().trimmed();
    if(acc == QString("") || pass == QString("")){
        QMessageBox::warning(this, "错误", "账户/密码不能为空", QMessageBox::Yes);
        return;
    }
    switch (check(acc, pass)) {
    case 0:
        QMessageBox::warning(this, "错误", "密码错误，请重新输入", QMessageBox::Yes);
        return;break;
    case 1:
        Now_User = acc;
        accept();
        break;
    case 2:
        QMessageBox::warning(this, "错误", "账户不存在，请重新输入", QMessageBox::Yes);
        ui->Account->clear();ui->Account->setFocus();
        break;
    }
    ui->Password->clear();
}
void Login::regist(QString Acc, QString Pass){
    Pass = encrypto(Pass);
    Password[Acc]=Pass;
}
void Login::Loaddata(){
    QFile Pfile("./password");
    Pfile.open(QIODevice::ReadOnly|QIODevice::Text);
    QString Acc, Pas, _tmp;
    while(!Pfile.atEnd()){
        _tmp = Pfile.readLine().trimmed() ;
        int space = _tmp.indexOf(" ");
        Acc = _tmp.mid(0, space-1);
        Pas = _tmp.mid(space+1);
        Password[Acc] = Pas;
    }
}

int Login::check(QString Acc, QString Pass){
    Pass = encrypto(Pass);
    if(Password.find(Acc)==Password.end()) return 2; // account does not exist;
    if(Password[Acc] != Pass) return 0; // wrong password;
    return 1;
}

QString Login::encrypto(QString &pass){
    return QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Md5).toHex();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
New_Account_ui::New_Account_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Account_ui)
{
    setFixedSize(400, 247);
    ui->setupUi(this);
}

New_Account_ui::~New_Account_ui()
{
    delete ui;
}
void New_Account_ui::on_Signin_Bot_clicked(){
    QString acc = ui->Account->text().trimmed();
    QString pass = ui->Password->text().trimmed();
    if(acc == QString("") || pass == QString("")){
        QMessageBox::warning(this, "错误", "账户/密码不能为空", QMessageBox::Yes);
        return;
    }
    if(data->check(acc, pass)==2){
        data->regist(acc, pass);
        //int aaa = Password.size();
        QDialog::accept();
    }
    else{
        QMessageBox::warning(this, "错误", "该帐户名已被申请，请重新选择", QMessageBox::Yes);
        ui->Account->setFocus();
    }
}
