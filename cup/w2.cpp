#include "w2.h"
#include "ui_w2.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>

w2::w2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w2)
{
    ui->setupUi(this);
    connectDB();
}

w2::~w2()
{
    delete ui;
}

//void genenrate_password(); //生成密码库
//void write_DB(QString numid);//写入数据库

void w2::write_DB(QString numid)//写入数据库 考虑到重名的情况，这里表名列为名字对应的序号numid，即大表的码
{

    QSqlQuery sql_query(db2);


    QString clear_sql = QString("drop table %1").arg(numid);
    sql_query.exec(clear_sql);

    QString create_sql =QString("create table %1 (code_dic VARCHAR(30))").arg(numid);

    sql_query.prepare(create_sql);
    if(!sql_query.exec(create_sql))
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    bool bsuccess = false;

    // 开始启动事务
    db2.transaction();
    QTime  tmpTime;
    tmpTime.start();

    int size_vector=PI.finalResualt.size();
    qDebug()<<"PI.finalResualt.size()="<<size_vector<<endl;
    for(int i=0;i<size_vector;i++)
    {
        QString insert1_sql =QString("insert into '%1'(code_dic) values('%2')")
                            .arg(numid)
                            .arg(PI.finalResualt[i]);
        bsuccess = sql_query.exec(insert1_sql);
        if (!bsuccess)
         qDebug()<<"Error occur"<<sql_query.lastError();
    }

//    // 提交事务，这个时候才是真正打开文件执行SQL语句的时候
    db2.commit();
    qDebug()<<"插入数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;

}

void w2::genenrate_password()//生成密码库
{
    qDebug() <<"*****7"<<endl;
    QStringList word1=PI.raw_read(ui->thename->text()+";"
                                  +ui->fam_bro_sis->text()+";"
                                  +ui->fam_children->text()+";"
                                  +ui->fam_frients->text()+";"
                                  +ui->fam_lover->text()+";"
                                  +ui->fam_parents->text()+";"
                                  +ui->fam_s->text());
    qDebug() <<"*****8"<<endl;
    qDebug() <<word1.length()<<endl;
    qDebug() <<word1.size()<<endl;
    for(int i=0;i<word1.size();i++)
    {
        qDebug() <<"90"<<endl;
        QString te =word1.at(i);
        qDebug() <<te<<endl;
        PI.dName(te);
    }


    //（如果不存在空格）short_name  like_组 fam_组  company_stname  other_strings
     word1=PI.raw_read(ui->short_name->text()+";"
                                  +ui->like_city->text()+";"
                                  +ui->like_pet->text()+";"
                                  +ui->like_sport->text()+";"
                                  +ui->like_star->text()+";"
                                  +ui->like_s->text()+";"
                                  +ui->fam_bro_sis->text()+";"
                                  +ui->fam_children->text()+";"
                                  +ui->fam_frients->text()+";"
                                  +ui->fam_lover->text()+";"
                                  +ui->fam_parents->text()+";"
                                  +ui->fam_s->text()+";"
                                  +ui->company_stname->text()+";"
                                  +ui->other_strings->text());
     qDebug() <<"****11"<<endl;

     for(int i=0;i<word1.size();i++)
     {

         QString temp=word1.at(i);
         if(temp.indexOf(" ")>-1)//判断是否有空格
            PI.dShortName(word1.at(i));
     }

     //3.(如果存在空格) province shi ......like_组 company_name  other_strings
     //    首字母缩写串 psj/PSJ
    // void d_Shortname(QString name)
     word1=PI.raw_read(ui->province->currentText() +";"
                      +ui->shi->currentText() +";"
                      +ui->xian->currentText() +";"
                      +ui->cun->currentText() +";"
                      +ui->zheng->currentText() +";"
                      +ui->like_city->text()+";"
                      +ui->like_pet->text()+";"
                      +ui->like_sport->text()+";"
                      +ui->like_star->text()+";"
                      +ui->like_s->text()+";"
                      +ui->company_name->text()+";"
                      +ui->other_strings->text());
     for(int i=0;i<word1.size();i++)
     {
         QString temp=word1.at(i);
         if(temp.indexOf(" ")==-1)//判断是否有空格
            PI.d_Shortname(word1.at(i));
     }
     qDebug() <<"****10"<<endl;
     // 4.从old_code 中提取的字符串以：  全大+全小：HD  hd
    // void d_selec_str(QString str)
      word1=PI.raw_read(ui->other_code->text());
      for(int i=0;i<word1.size();i++)
      {
          PI.d_selec_str(word1.at(i));
      }
      //    出生日期全  年|月|日  月+日 | 年+月  | 年+日(或者采用只抽取年月日，然后数字排列组合！！！！不行，不好把握组合数字的次数)
      //    有重要意义的日子（规定格式为0000：00：00）
      //    void d_data(QString dat)
      word1=PI.raw_read(ui->birth_year->currentText()+":"+ui->birth_month->currentText()+":"+ui->birth_day->currentText()+";"+ui->import_data->text());
      for(int i=0;i<word1.size();i++)
        PI.d_data(word1.at(i));
      //    身份证
      //    排列顺序从左至右依次为：六位数字地址码，八位数字出生日期码，三位数字顺序码和一位数字校验
      word1=PI.raw_read(ui->ID->text());
      for(int i=0;i<word1.size();i++)
            PI.d_ID(word1.at(i));
      //    手机号
      //    手机号前3位如170/150/136等是网络识别号,中间四位是地区编码,最后四位是用户号码
      //    取后四位，中间四位，前面三位（手机尽量填多个） +全部
      //    如果手机号=7位或者=5位 全部|后四位
      //    香港：9或6开头后面跟7位数字  澳门：66或68开头后面跟5位数字
      //    void d_phone(QString phonenum)
      word1=PI.raw_read(ui->phone->text());
      for(int i=0;i<word1.size();i++)
            PI.d_ID(word1.at(i));
      //    QQ号 全
      //    void d_qq(QString qqnum)
      word1=PI.raw_read(ui->qq->text());
      for(int i=0;i<word1.size();i++)
            PI.d_qq(word1.at(i));
  qDebug() <<"*****6"<<endl;
      // .从old_code 中提取的特殊符号
    // void d_selec_specia(QString str)
      word1=PI.raw_read(ui->other_code->text());
      for(int i=0;i<word1.size();i++)
            PI.d_selec_specia(word1.at(i));

 qDebug() <<"*****67"<<endl;
  //    微信号（提取数字）旧密码（提取数字）
  //    图腾数字、其他未提及的数字串
     // void d_selec_num(QString str)

      word1=PI.raw_read(ui->other_code->text()+";"+ui->other_num->text()+";"+ui->import_num->text());
      for(int i=0;i<word1.size();i++)
            PI.d_selec_num(word1.at(i));

      PI.generateDic(ui->check_special->text().toInt(),ui->check_add->text().toInt());
}

void w2::connectDB() //连接数据库
{
//    if(QSqlDatabase::contains("qt_sql_default_connection"))
//            QSqlDatabase::removeDatabase("qt_sql_default_connection");
//         db2 = QSqlDatabase::addDatabase("QSQLITE");
    if(QSqlDatabase::contains("qt_sql_default_connection"))
                 db2 = QSqlDatabase::database("qt_sql_default_connection");
               else
                 db2 = QSqlDatabase::addDatabase("QSQLITE");
        db2.setDatabaseName("D:\\qtcode\\build-cup-Desktop_Qt_5_6_3_MinGW_32bit-Debug\\cup.db");
        //打开数据库
        if(!db2.open())
        {
            QMessageBox::warning(this, "数据库打开失败", db2.lastError().text());
            return;
        }


}

void w2::on_pushButton_released()
{
    QSqlQuery query(db2);
    QString sql = QString("INSERT INTO mycup (name,short_name,birth_year,birth_month,birth_day,"
                          "addr_shen,addr_shi,addr_xian,addr_zhen,addr_cun,Idcard,"
                          "qqnum,Wechat,social_name,company_name,company_stname,"
                          "like_pet,like_star,like_sport,like_city,like_s,fam_lover,"
                          "fam_children,fam_parents,fam_bro_sis,fam_frients,fam_s,"
                          "other_strings,import_data,import_num,other_num,other_code,"
                          "check_add,check_special,phone) VALUES ('%1','%2','%3','%4','%5','%6',"
                          "'%7','%8','%9','%10','%11','%12','%13','%14','%15','%16',"
                          "'%17','%18','%19','%20','%21','%22','%23','%24','%25','%26',"
                          "'%27','%28','%29','%30','%31','%32','%33','%34','%35')")
                   .arg(ui->thename->text())
                   .arg(ui->short_name->text())
                   .arg(ui->birth_year->currentText())
                   .arg(ui->birth_month->currentText())
                   .arg(ui->birth_day->currentText())
                   .arg(ui->province->currentText())
                   .arg(ui->shi->currentText())
                   .arg(ui->xian->currentText())
                   .arg(ui->zheng->currentText())
                   .arg(ui->cun->currentText())
                   .arg(ui->ID->text())
                   .arg(ui->qq->text())
                   .arg(ui->wechat_num->text())
                   .arg(ui->socialname->text())
                   .arg(ui->company_name->text())
                   .arg(ui->company_stname->text())
                   .arg(ui->like_pet->text())
                   .arg(ui->like_star->text())
                   .arg(ui->like_sport->text())
                   .arg(ui->like_city->text())
                   .arg(ui->like_s->text())
                   .arg(ui->fam_lover->text())
                   .arg(ui->fam_children->text())
                   .arg(ui->fam_parents->text())
                   .arg(ui->fam_bro_sis->text())
                   .arg(ui->fam_frients->text())
                   .arg(ui->fam_s->text())
                   .arg(ui->other_strings->text())
                   .arg(ui->import_data->text())
                   .arg(ui->import_num->text())
                   .arg(ui->other_num->text())
                   .arg(ui->other_code->text())
                   .arg(ui->check_add->text().toInt())//失灵了，怎么回事
                   .arg(ui->check_special->text().toInt())//失灵了，怎么回事
                   .arg(ui->phone->text());
    if(ui->thename->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("懒到连名字都不输？？");
           msgBox.exec();
    }
    else
    { query.exec(sql);
        //生成密码库
        qDebug() <<"*****4"<<endl;
           genenrate_password();
            qDebug() <<"*****5"<<endl;
           //查找name对应的key_id

           QString sql2 =QString("select my_id from mycup where name = '%1'")
                           .arg(ui->thename->text());
           query.exec(sql2);
           QString temp2;
           while( query.next())
               temp2=query.value("my_id").toString();
           //写入数据库
           temp2="xx"+temp2;
           qDebug() <<"*****2"<<endl;

            qDebug() <<temp2<<endl;
           qDebug() <<"*****"<<endl;

           write_DB(temp2);
       QMessageBox msgBox;
       msgBox.setText("密码库生成辽！！！");
          msgBox.exec();
    }

        db2.close();

}
