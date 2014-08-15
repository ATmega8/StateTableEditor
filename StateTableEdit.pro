#-------------------------------------------------
#
# Project created by QtCreator 2014-08-08T23:16:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StateTableEdit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treemodel.cpp \
    treeitem.cpp

HEADERS  += mainwindow.h \
    treemodel.h \
    treeitem.h

FORMS    += mainwindow.ui
