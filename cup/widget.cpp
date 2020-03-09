#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_change_button_released()
{
    widget1.show();
    this->close();

}

void Widget::on_new_button_released()
{
    widget2.show();
    this->close();
}
