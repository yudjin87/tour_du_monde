include(../shared.pri)

QT       += gui
QT       += testlib

TEMPLATE = app

TARGET = geodatabase_test

LIBS += -L$${CAROUSEL_BIN} -lutils \
                           -lcomponentsystem \
                           -lframework \

LIBS += -L$${DESTDIR}/components -lgeodatabase
LIBS += -L$${DESTDIR}            -lgeometry \

SOURCES += \
    main_geodatabase_test.cpp \
    ShapeFileFeatureDatasetTest.cpp \
    ShapeFileReaderTest.cpp \
    fakes/FakeWorkspace.cpp \
    fakes/FakeShapeFileReader.cpp \
    fakes/FakeShapeFileFeatureDataset.cpp \
    fakes/FakeGeometryFactory.cpp \
    fakes/FakeFeatureClass.cpp \
    fakes/FakeFeature.cpp

HEADERS += \
    ShapeFileFeatureDatasetTest.h \
    ShapeFileReaderTest.h \
    fakes/FakeWorkspace.h \
    fakes/FakeShapeFileReader.h \
    fakes/FakeShapeFileFeatureDataset.h \
    fakes/FakeGeometryFactory.h \
    fakes/FakeFeatureClass.h \
    fakes/FakeFeature.h
