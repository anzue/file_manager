#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T18:22:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = file_manager
TEMPLATE = app


SOURCES += main.cpp\
        manager.cpp \
    panel.cpp \
    texteditor.cpp \
    infopanel.cpp

HEADERS  += manager.h \
    panel.h \
    texteditor.h \
    infopanel.h

FORMS    += manager.ui \
    texteditor.ui \
    infopanel.ui
