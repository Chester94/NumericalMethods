#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T15:44:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumericalMethods
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    function.cpp \
    polynomial.cpp

HEADERS  += mainwindow.h \
    function.h \
    polynomial.h

FORMS    += mainwindow.ui
CONFIG += qwt
