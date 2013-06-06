#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T16:55:51
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Topology
TEMPLATE = app


SOURCES += main.cpp\
        topologydialog.cpp \
    info.cpp

HEADERS  += topologydialog.h \
    info.h

FORMS    += topologydialog.ui

RESOURCES += \
    resource.qrc
