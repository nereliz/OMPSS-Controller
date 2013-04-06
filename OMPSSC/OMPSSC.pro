#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T11:36:54
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql
QT       += script

QT       -= gui

TARGET = OMPSSC
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Controller.cpp \
    task.cpp

HEADERS += \
    Controller.h \
    task.h

OTHER_FILES += \
    config.ini
