TEMPLATE = app

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp

RESOURCES += \
    map.qrc

DESTDIR = $$PWD

CONFIG += c++11

include (./../qsimplespatial/qsimplespatial_static.pri)
