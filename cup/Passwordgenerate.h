#ifndef __PASSWORDGENERATE__H__
#define __PASSWORDGENERATE__H__
#include <iostream>
#include <QString>
#include <QStringList>
#include <vector>
#include <algorithm>
#include <QRegExp>
#include <QDebug>
#include <QFile>

//QDomNodeList
using namespace std;
class Passwordgenerate{
    //加上csdn密码分析提供的原始密码字段
public :

    //旧密码
    vector<QString> Oldpassword;//加入finalResualt
    //关键数字
    vector<QString> numList={"1234"};
   // vector<QString> numList_from_oldcode={};
    //关键字母串
     vector<QString> wordList={"love","qq","password"};
   //  vector<QString> wordList_from_oldcode={};
    //最终结果
    vector<QString> finalResualt;
    //提供的特殊字符库
    vector<QString> Spacialist={"@","#","$","%","^","&","*","-","/","?"};
   // vector<QString> Spacialist_from_oldcode={};
    //提供推荐密码
    vector<QString> Addlist={};


    int max_len=20;//密码最大长度
    int min_len=6;//密码最小长度

public:
    //实现切割 空白字符缩减
    QStringList raw_read(QString raw)
    {
        raw=raw.simplified();//将多个空格缩减为一个空格
        QStringList list = raw.split(";");
        list.removeAll("");
        list.removeAll(" ");
        return list;

    }

//    //实现addlist 友情附赠
//    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
//        db.setDatabaseName("test.db");
//        //打开数据库
//        if(!db.open())
//        {
//            QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
//            return;
//        }
//         QSqlQuery sql_query(db);

//         QString create_sql =QString("create table pre_code (code_dic VARCHAR(30))");

//         sql_query.prepare(create_sql);
//         if(!sql_query.exec(create_sql))
//         {
//             qDebug() << "Error: Fail to create table." << sql_query.lastError();
//         }
//         else
//         {
//             qDebug() << "Table created!";
//         }
//         bool bsuccess = false;

//      //打开txt

//    QStringList fonts;
//    QFile file("D:\\qtcode\\test1\\pre_code.txt");
//          if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//          {
//              qDebug()<<"error";
//              return;
//          }

//           qDebug()<<"55"<<endl;
//          QTextStream in(&file);
//          while (!in.atEnd()) {
//              fonts.push_back(in.readLine());}
//          qDebug()<<"59"<<endl;

//          // 开始启动事务
//          db.transaction();
//          QTime  tmpTime;
//          tmpTime.start();

//          int size_vector=fonts.size();
//          qDebug()<<"fonts.size()="<<size_vector<<endl;
//          for(int i=0;i<size_vector;i++)
//          {
//              bsuccess = sql_query.exec(QString("insert into pre_code values('%1')")
//                                        .arg(fonts[i]));
//              if (!bsuccess)
//               qDebug()<<"Error occur"<<sql_query.lastError();
//          }

//      //    // 提交事务，这个时候才是真正打开文件执行SQL语句的时候
//          db.commit();
//          qDebug()<<"插入数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;

//    1.thename  fam_组：
    //    首字母缩写串 psj/PSJ
    //    姓氏 大+小：PENG/peng/Peng

//    2.（如果不存在空格）short_name  like_组 fam_组  company_stname  other_strings
//    全大+全小：HD  hd
//    3.(如果存在空格) province shi ......like_组 company_name  other_strings
//    首字母缩写串 psj/PSJ

//    4.从old_code 中提取的字符串以：  全大+全小：HD  hd

    //1.thename  fam_组：
   // 首字母缩写串 psj/PSJ/P/p/首字母缩写串-p（P）/（复姓）取前两个首字母大+小
    //姓氏 大+小：PENG/peng/Peng/（复姓）sheng Sheng SHENG
    //假设我已经得到以空格分割的名字拼音或者其他啥
    void dName(QString name)
    {
        qDebug()<<"000000a"<<endl;
        QStringList list = name.split(" ");//QString字符串分割函数
        QString name_word;
        QString a;//psj
        QString b;//p
        QString c;//（复姓）取前两个首字母大+小,判断与a相不相等
        QString d=list.at(0);//PENG
        QString e;//sheng 其实是找（复姓）ouyang

        for(int i = 0; i< list.size();i++)
        {

            QString temp = list.at(i);
            name_word+=temp;

            if(i==0)
            {
                b=temp.at(0);
                d=temp;
                c=b;
            }

            if(i==1)
            {
                c+=temp.at(1);
                e=temp;
            }

            a+=temp.at(0);

        }

        wordList.push_back(name_word.toUpper());
        wordList.push_back(name_word.toLower());

        wordList.push_back(a.toUpper());
        wordList.push_back(a.toLower());
        wordList.push_back(b.toUpper());
        wordList.push_back(b.toLower());

        if(a.size()>1)
        {
            QString temp=a.mid(1);

            wordList.push_back(temp.toUpper());
            wordList.push_back(temp.toLower());
        }

        if(c.toLower()!=a.toLower())
        {
            wordList.push_back(c.toUpper());
            wordList.push_back(c.toLower());
        }
        wordList.push_back(d.toUpper());
        wordList.push_back(d.toLower());
        QString temp=d.toUpper()+d.toLower();
        wordList.push_back(temp);
        temp=d.toLower()+d.toUpper();
        wordList.push_back(temp);
        if(d.size()>1)
        {
            temp=d.toLower().mid(1);
        }

       temp=b.toUpper()+temp;
       wordList.push_back(temp);
       if(c.toLower()!=a.toLower())
       {
           temp=d.toUpper()+e.toUpper();
           wordList.push_back(temp);
           temp=d.toLower()+e.toLower();
           wordList.push_back(temp);
       }
    }
    //    2.（如果不存在空格）short_name  like_组 fam_组  company_stname  other_strings
    //    全大+全小：HD  hd
    void dShortName(QString name)
    {
        wordList.push_back(name.toUpper());
        wordList.push_back(name.toLower());

        qDebug()<<"00000qw"<<endl;

    }
    //3.(如果存在空格) province shi ......like_组 company_name  other_strings
    //    首字母缩写串 psj/PSJ
    void d_Shortname(QString name)
    {
        QStringList list = name.split(" ");//QString字符串分割函数
        QString a;//psj
        for(int i = 0; i< list.size();++i)
             a+=list.at(i);
        wordList.push_back(a.toUpper());
        wordList.push_back(a.toLower());

        qDebug()<<"00000qw1"<<endl;


    }

    // 4.从old_code 中提取的字符串以：  全大+全小：HD  hd
    void d_selec_str(QString str)
    {
        vector<QString> * wordList_from_oldcode=new vector<QString>();
        QRegExp rx("[a-zA-Z]+");
        int pos = 0;
        while ((pos = rx.indexIn(str, pos)) != -1)
        {
                wordList_from_oldcode->push_back(rx.cap(0));
               pos += rx.matchedLength();
        }
        qDebug()<<"00000qw2"<<endl;
        wordList.insert(wordList.begin(),wordList_from_oldcode->begin(),wordList_from_oldcode->end());
    }


//    出生日期全  年|月|日  月+日 | 年+月  | 年+日(或者采用只抽取年月日，然后数字排列组合！！！！不行，不好把握组合数字的次数)
//    有重要意义的日子（规定格式为0000：00：00）
    void d_data(QString dat)
    {
        QStringList datlist = dat.split(":");//QString字符串分割函数
        QString a,b,c;
        if(datlist.size()>0)
          a=datlist.at(0);//年
        if(datlist.size()>1)
         b=datlist.at(1);//月
        if(datlist.size()>2)
         c=datlist.at(2);//日
        if(a!="0000")
            numList.push_back(a);
        if(b!="00")
            numList.push_back(b);
        if(c!="00")
            numList.push_back(c);
        if(a!="0000"&&b!="00"&&c!="00")
        {
            numList.push_back(a+b+c);
            numList.push_back(b+c+a);
            numList.push_back(c+b+a);
        }

        if(a!="0000"&&b!="00")
        {
            numList.push_back(a+b);
            numList.push_back(b+a);
        }

        if(b!="00"&&c!="00")
        {
           numList.push_back(b+c);
           numList.push_back(c+b);
        }
        if(a!="0000"&&c!="00")
        {
            numList.push_back(a+c);
            numList.push_back(c+a);
        }
qDebug()<<"00000qw3"<<endl;

    }


//    身份证
//    排列顺序从左至右依次为：六位数字地址码，八位数字出生日期码，三位数字顺序码和一位数字校验
    void d_ID(QString idnum)
    {
        if(idnum.length()==18)
        {
        numList.push_back(idnum.mid(0,6));
        numList.push_back(idnum.mid(6,8));
        numList.push_back(idnum.mid(14,4));
        }
        qDebug()<<"00000qw4"<<endl;


    }

//    手机号
//    手机号前3位如170/150/136等是网络识别号,中间四位是地区编码,最后四位是用户号码
//    取后四位，中间四位，前面三位（手机尽量填多个） +全部
//    如果手机号=7位或者=5位 全部|后四位
//    香港：9或6开头后面跟7位数字  澳门：66或68开头后面跟5位数字
    void d_phone(QString phonenum)
    {
        if(phonenum.length()==11)
        {
            numList.push_back(phonenum.mid(0,3));
            numList.push_back(phonenum.mid(3,4));
            numList.push_back(phonenum.mid(7,4));
            numList.push_back(phonenum);
        }
        else if(phonenum.length()==7||phonenum.length()==5)
        {
            int a=phonenum.length()-4;
            numList.push_back(phonenum.mid(a,4));
            numList.push_back(phonenum);
        }
        qDebug()<<"00000qw5"<<endl;

    }

//    QQ号 全
    void d_qq(QString qqnum)
    {
        if(qqnum.length()>0)
        numList.push_back(qqnum);
         qDebug()<<"00000qw6"<<endl;

    }

//    微信号（提取数字）旧密码（提取数字）
//    图腾数字、其他未提及的数字串
    void d_selec_num(QString str)
    {
         vector<QString> *numList_from_oldcode=new vector<QString>();
        qDebug()<<"*****qw7"<<endl;
        if(str.length()>0)
        {
            QRegExp rx("[0-9][0-9]*");
            int pos = 0;
            while ((pos = rx.indexIn(str, pos)) != -1)
            {
                    numList_from_oldcode->push_back(rx.cap(0));
                   pos += rx.matchedLength();
            }

        }
        numList.insert(numList.begin(),numList_from_oldcode->begin(),numList_from_oldcode->end());
        qDebug()<<"00000qw7"<<endl;

    }
     // .从old_code 中提取的特殊符号
    void d_selec_specia(QString str)
    {
        vector<QString> *Spacialist_from_oldcode=new vector<QString>();
        qDebug()<<"*****qw8"<<endl;
        if(str.length()>0)
         {
            QRegExp rx("[^0-9a-zA-Z]");
            int pos = 0;
            while ((pos = rx.indexIn(str, pos)) != -1)
            {

                    Spacialist_from_oldcode->push_back(rx.cap(0));//special也分两类，一类是从旧密码里提取出来的，先进行排列组合，剩下是类提供的，后组合
                   pos += rx.matchedLength();
                   //qDebug()<<rx.cap(0);
            }
        }
        Spacialist.insert(Spacialist.begin(),Spacialist_from_oldcode->begin(),Spacialist_from_oldcode->end());
        qDebug()<<"00000qw8"<<endl;
    }
    //不采用这个方式的原因是因为造成了内存不够2019.10.23

//    //实现特殊符号的权重，或者，从旧密码中提取的所有字符串，数字串的权重都提高，算啦，随他去了吧
//可以这样，六个vector分别simple_vector，然后混合,设置权重，意味着混合old的操作要最后进行，所以应设置为全局变量。
//    void set_weight(vector<QString>& v,vector<QString>& vv)
//    {
//        simple_vector(v);
//        simple_vector(vv);
//        v.insert(v.begin(),vv.begin(),vv.end());
//        v.erase(unique(v.begin(),v.end()),v.end());
//    }

//    //去重
    void simple_vector(vector<QString>& v)
    {
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        qDebug()<<"00000qw9"<<endl;
    }


    //混合1
   void dMix(vector<QString> ud)
   {
       int j=ud.size();
       int i=0;
      QString udd;
       for(;i<j;i++)
       {
           udd=ud[i];
           int sum=udd.size();
           if((min_len<=sum)&&(sum<=max_len))
           {
               finalResualt.push_back(udd);
           }
       }
   }

   //混合2
    void dMix(vector<QString> t1,vector<QString> t2)
   {
       for(auto a:t1)
       {
           for(auto b:t2)
           {
               QString s;
               s=a+b;
               int sum=s.size();
              if((min_len<=sum)&&(sum<=max_len))
              finalResualt.push_back(s);

           }
       }

   }
    //混合3

    void dMix(vector<QString> t1,vector<QString> t2,vector<QString> t3)
   {
       for(auto a:t1)
       {
           for(auto b:t2)
           {
              for(auto c:t3)
              {
                  QString s;
                  s=a+b+c;
                  int sum=s.size();
                  if((min_len<=sum)&&(sum<=max_len))
                      finalResualt.push_back(s);
              }
           }
       }
   }
    //开始混合
    // vector<QString> numList;
    //关键字母串
     //vector<QString> wordList;
    void generateDic(int add_special,int add_list)
    {
        qDebug()<<"c"<<endl;

        simple_vector(numList);
        simple_vector(wordList);
        simple_vector(Spacialist);


        dMix(wordList);
        dMix(numList);

        dMix(numList,numList);
        dMix(wordList,numList);
        dMix(numList,wordList);
        dMix(numList,numList,wordList);
        dMix(numList,wordList,wordList);
        dMix(wordList,wordList,numList);
        if(add_special==1)
        {
            dMix(Spacialist,numList,wordList);
            dMix(numList,numList,Spacialist);
            dMix(wordList,numList,Spacialist);
            dMix(numList,Spacialist);
            dMix(Spacialist,wordList,Spacialist);
        }
        numList.~vector();
        wordList.~vector();
        Spacialist.~vector();
        qDebug()<<"cccccc "<<endl;
        finalResualt.insert(finalResualt.end(),Oldpassword.begin(),Oldpassword.end());

        Oldpassword.~vector();

        if(add_list==1)
        {
            //那就 使用pre表 约15000条
           finalResualt.insert(finalResualt.end(),Addlist.begin(),Addlist.end());
        }
        Addlist.~vector();

        qDebug()<<"good!"<<endl;


    }







};
#endif
