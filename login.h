#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "stdafx.h"
#include <QCryptographicHash> //用MD5加密密码
#include <QFile>
#include <QString>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
};

class Login_Utility
{
public:
    Login_Utility(){
        Load_Data();
    }
    int Check(QString acc, QString pass){
        return check(acc, pass);
    }
    int New_Account(QString account, QString password){
        return new_account(account, password);
    }
private:
    QString Secret_key = "anki_kong";
    map<QString, QString> Password;
    void Load_Data(){
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
    int check(QString account, QString password){
       //返回值说明：0：密码错误 1：认证成功 2：账户不存在
        if(Password.find(account)==Password.end())return 2;
        QByteArray cry_pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();
        if(Password[account]==cry_pass)return 1;
        return 0;
    }
    int new_account(QString account, QString password){
        //返回值说明：0：账号已存在 1：注册成功
        //校验账号是否存在
        if(check(account, password)==2){
            QByteArray cry_pass = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();
            Password[account] = cry_pass;
            return 1;
        }
        else
            return 0;
    }
};

#endif // LOGIN_H
