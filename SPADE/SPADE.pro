#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T22:55:30
#
#-------------------------------------------------
QT += core
QT -= gui

CONFIG += c++11

TARGET = SPADE
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    datasetreader.cpp \
    idlist.cpp \
    spade.cpp \
    sequence.cpp \
    closedseqrep.cpp \
    transaction.cpp \
    filehelper.cpp \
    generatorsreppositiveborder.cpp \
    generatorsrepnegativeborder.cpp \
    representation.cpp \
    sequencescalculator.cpp \
    tictoc.cpp

HEADERS += \
    datasetreader.h \
    idlist.h \
    spade.h \
    sequence.h \
    closedseqrep.h \
    transaction.h \
    filehelper.h \
    generatorsreppositiveborder.h \
    generatorsrepnegativeborder.h \
    representation.h \
    sequencescalculator.h \
    tictoc.h
