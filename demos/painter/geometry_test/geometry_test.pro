include(../shared.pri)

QT       += gui
QT       += testlib

TEMPLATE = app

TARGET = geometry_test

LIBS += -L$${DESTDIR} -lgeometry \

SOURCES += \
    main_geometry_test.cpp \
    GeometryFactoryTest.cpp

HEADERS += \
    GeometryFactoryTest.h
