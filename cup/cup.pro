#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T13:04:03
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cup
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    w1.cpp \
    w2.cpp \
    UIChinaCity.cpp \
    chineseletterhelper.cpp

HEADERS  += widget.h \
    w1.h \
    w2.h \
    Passwordgenerate.h \
    UIChinaCity.h \
    chineseletterhelper.h

FORMS    += widget.ui \
    w1.ui \
    w2.ui
