#include "login.h"
#include "ui_login.h"

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
