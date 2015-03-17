include(../shared.pri)

QT       += gui
QT       += testlib

TEMPLATE = app

TARGET = geometry_test

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geometry \
                      -lorg.carousel.demos.Geodatabase

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.JsScripting \

SOURCES += \
    main_geometry_test.cpp \
    GeometryFactoryTest.cpp

HEADERS += \
    GeometryFactoryTest.h
