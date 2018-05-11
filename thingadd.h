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
namespace Ui {
class ThingAdd;
class Thing_Tag_Select;
}

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


class Thing_Tag_Select : public QWidget {
    Q_OBJECT
public:
    explicit Thing_Tag_Select(QWidget *parent = 0);
    ~Thing_Tag_Select();
    vector<QCheckBox*> initWidget(vector<QString> Tag_Sum);
private:

};
#endif // THINGADD_H
