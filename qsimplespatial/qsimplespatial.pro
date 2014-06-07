TEMPLATE = lib

QT  += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSimpleSpatial

SOURCES += \
    shapemapreader.cpp \
    pointfeature.cpp \
    feature.cpp \
    mapframe.cpp \
    maptranslator.cpp \
    projection.cpp \
    polygonfeature.cpp \
    paintscheme.cpp \
    layer.cpp \
    polylinefeature.cpp \
    paintschemepoint.cpp \
    paintschemepolygon.cpp \
    labelscheme.cpp \
    paintschemepolyline.cpp \
    projection_wgs84_worldmercator.cpp \
    projection_wgs84_sphericalmercator.cpp

HEADERS += \
    shapemapreader.h \
    pointfeature.h \
    mapreader.h \
    mapglobal.h \
    feature.h \
    mapframe.h \
    maptranslator.h \
    projection.h \
    polygonfeature.h \
    paintscheme.h \
    layer.h \
    polylinefeature.h \
    paintschemepoint.h \
    paintschemepolygon.h \
    labelscheme.h \
    paintschemepolyline.h \
    projection_wgs84_worldmercator.h \
    projection_wgs84_sphericalmercator.h \
    mapwriter.h \
    shapeglobal.h

include(../qdbf/qdbf_static.pri)

CONFIG += c++11

#QMAKE_CXXFLAGS_DEBUG += -g3 -pg
#QMAKE_LFLAGS_DEBUG += -pg -lgmon

