#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T15:23:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = font_converter
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    ../../display/fonts/DefaultFonts.c \
        convertfontdialog.cpp \
    fontconverter.cpp \
    selectcharintervaldialog.cpp

HEADERS  += convertfontdialog.h \
    ../../display/fonts/DefaultFonts.h \
    fontconverter.h \
    selectcharintervaldialog.h
