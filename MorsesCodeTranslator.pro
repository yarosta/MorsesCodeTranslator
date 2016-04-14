#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T00:00:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MorsesCodeTranslator
TEMPLATE = app


SOURCES += main.cpp\
        translatorwindow.cpp \
    translatorview.cpp \
    translatormodel.cpp

HEADERS  += translatorwindow.h \
    translatorview.h \
    translatormodel.h

FORMS    += translatorwindow.ui

RESOURCES += \
    resources.qrc
