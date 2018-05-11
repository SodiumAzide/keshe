#ifndef THINGADD_H
#define THINGADD_H

#include <QDialog>

namespace Ui {
class ThingAdd;
}

class ThingAdd : public QDialog
{
    Q_OBJECT

public:
    explicit ThingAdd(QWidget *parent = 0);
    ~ThingAdd();

private:
    Ui::ThingAdd *ui;
private slots:
    void on_Thing_Confirm_clicked();
};

#endif // THINGADD_H
