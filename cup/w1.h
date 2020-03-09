#ifndef W1_H
#define W1_H

#include <QWidget>
#include "Passwordgenerate.h"
#include <QSqlDatabase>

namespace Ui {
class w1;
}

class w1 : public QWidget
{
    Q_OBJECT

public:
    explicit w1(QWidget *parent = 0);
    ~w1();
    void connectDB(); //连接数据库
    void genenrate_password(); //生成密码库
    void write_DB(QString numid);//写入数据库
    Passwordgenerate PI;
    QSqlDatabase db1;






private slots:
    //void on_name_currentIndexChanged(const QString &arg1);

    void on_thename_currentIndexChanged(const QString &arg1);

    void on_pushButton_released();


private:
    Ui::w1 *ui;


};

#endif // W1_H
