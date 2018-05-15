#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFile>
#include <QString>

#ifndef STDAFX_H
#include "stdafx.h"
#endif
#ifndef THING_H
#include "thing.h"
#endif
//extern QString DATA_FILE;
//extern map<QString, vector<ll> > TagToThing;
namespace Ui {
class Login;
class New_Account_ui;
class ChangePass;
}
//QString DATA_FILE = "./data.txt";
//////////////////////////////////////

/////////////////////////////////////

class Login : public QDialog
{
    Q_OBJECT

public:
    struct Detail
    {
        Detail() {}
        QString Password, Name;
    };
    explicit Login(QWidget *parent = 0);
    ~Login();
    void login();
    void regist(QString Acc, QString Pass, QString Name);
    void change_password();
    void Loaddata();
    int  check(QString Acc, QString Pass);
    QString Now_User;
    map<QString, Detail> Password;

private:
    Ui::Login *ui;
    int addAcc(QString acc, QString pass);
    QString encrypto(QString &pass);


private slots:
    void on_New_Account_clicked();
    void on_Login_Bot_clicked();
};

////////////////////////////////////////////////////////////////
class New_Account_ui : public QDialog
{
    Q_OBJECT

public:
    explicit New_Account_ui(QWidget *parent = 0);
    ~New_Account_ui();
    Login* data;

private:
    Ui::New_Account_ui *ui;

private slots:
    void on_Signin_Bot_clicked();
};

class ChangePass : public QDialog
{
    Q_OBJECT
public:
    ChangePass(QWidget *parent = 0, Login *dat=0);
    ~ChangePass();
    Login* data;
private:
    Ui::ChangePass *ui;
    QString encrypto(QString &pass);
private slots:
    void on_Confirm_clicked();
};

///////////////////////////////////////////////////////////////

#endif // LOGIN_H
