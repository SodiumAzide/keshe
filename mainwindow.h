#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "thing.h"
#include "login.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Thing *data=0, Login *secu=0);
    ~MainWindow();

    Thing *a;

private:
    Ui::MainWindow *ui;
    Login *security;
private slots:
    void datachange();
    void on_Search_clicked();
    void on_Add_Thing_clicked();
    void on_Help_clicked();
    void on_Security_clicked();
protected:
};



#endif // MAINWINDOW_H
