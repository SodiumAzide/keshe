#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFile>
#include <QString>

#ifndef STDAFX_H
#include "stdafx.h"
#endif
namespace Ui {
class Login;
class New_Account_ui;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void login();
    void regist(QString Acc, QString Pass);
    void change_password();
    void Loaddata();
    int  check(QString Acc, QString Pass);

private:
    Ui::Login *ui;
    map<QString, QString> Password;
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
#endif // LOGIN_H
