INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/shapemapreader.cpp \
    $$PWD/pointfeature.cpp \
    $$PWD/feature.cpp \
    $$PWD/mapframe.cpp \
    $$PWD/maptranslator.cpp \
    $$PWD/projection.cpp \
    $$PWD/polygonfeature.cpp \
    $$PWD/paintscheme.cpp \
    $$PWD/layer.cpp \
    $$PWD/polylinefeature.cpp \
    $$PWD/paintschemepoint.cpp \
    $$PWD/paintschemepolygon.cpp \
    $$PWD/labelscheme.cpp \
    $$PWD/paintschemepolyline.cpp \
    $$PWD/projection_wgs84_worldmercator.cpp \
    $$PWD/projection_wgs84_sphericalmercator.cpp

HEADERS += \
    $$PWD/shapemapreader.h \
    $$PWD/pointfeature.h \
    $$PWD/mapreader.h \
    $$PWD/mapglobal.h \
    $$PWD/feature.h \
    $$PWD/mapframe.h \
    $$PWD/maptranslator.h \
    $$PWD/projection.h \
    $$PWD/polygonfeature.h \
    $$PWD/paintscheme.h \
    $$PWD/layer.h \
    $$PWD/polylinefeature.h \
    $$PWD/paintschemepoint.h \
    $$PWD/paintschemepolygon.h \
    $$PWD/labelscheme.h \
    $$PWD/paintschemepolyline.h \
    $$PWD/projection_wgs84_worldmercator.h \
    $$PWD/projection_wgs84_sphericalmercator.h

include(../qdbf/qdbf_static.pri)
