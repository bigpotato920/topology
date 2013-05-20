#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T16:55:51
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Topology
TEMPLATE = app


SOURCES += main.cpp\
        toplogydialog.cpp \
    coordinate.cpp

HEADERS  += toplogydialog.h \
    coordinate.h

FORMS    += toplogydialog.ui

RESOURCES += \
    resource.qrc
