#ifndef W2_H
#define W2_H

#include <QWidget>
#include "Passwordgenerate.h"
#include <QSqlDatabase>

namespace Ui {
class w2;
}

class w2 : public QWidget
{
    Q_OBJECT

public:
    explicit w2(QWidget *parent = 0);
    ~w2();
    void connectDB(); //连接数据库

    void genenrate_password(); //生成密码库
    void write_DB(QString numid);//写入数据库
    Passwordgenerate PI;
    QSqlDatabase db2;


private slots:
    void on_pushButton_released();

private:
    Ui::w2 *ui;

};

#endif // W2_H
