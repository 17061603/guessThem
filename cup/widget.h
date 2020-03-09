#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "w1.h"//子窗口头文件
#include "w2.h"//子窗口头文件
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_change_button_released();

    void on_new_button_released();

private:
    Ui::Widget *ui;
    w1 widget1;
    w2 widget2;
};

#endif // WIDGET_H
