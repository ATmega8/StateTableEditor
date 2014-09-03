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
    settingdialog.cpp \
    parser.cpp \
    parsertreeitem.cpp \
    statetable.cpp \
    tableitem.cpp

HEADERS  += mainwindow.h \
    settingdialog.h \
    parser.h \
    parsertreeitem.h \
    statetable.h \
    tableitem.h

FORMS    += mainwindow.ui \
    settingdialog.ui

OTHER_FILES += \
    README.md
