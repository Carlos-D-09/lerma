#-------------------------------------------------
#
# Project created by QtCreator 2021-03-01T12:01:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lerma
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    productwidget.cpp

HEADERS  += mainwindow.h \
    user.h \
    productwidget.h

FORMS    += mainwindow.ui \
    productwidget.ui

RESOURCES += \
    images.qrc
