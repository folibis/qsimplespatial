TEMPLATE = subdirs

SUBDIRS += \
    qdbf \
    qsimplespatial \
    examples

CONFIG += c++11

CONFIG += ordered


#QMAKE_CXXFLAGS_DEBUG += -g3 -pg
#QMAKE_LFLAGS_DEBUG += -pg -lgmon
