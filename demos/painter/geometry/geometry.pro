include(../shared.pri)

QT       += gui

TEMPLATE = lib

TARGET = Geometry

DEFINES += GEOMETRY_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lUtils \
                           -lComponentSystem \
                           -lFramework \

DESTDIR = $${DESTDIR}/externalSource

HEADERS += \
    geometry_api.h \
    AbstractGeometry.h \
    Point.h \
    Segment.h \
    Ring.h \
    Polygon.h \
    GeometryType.h \
    Polyline.h \
    IGeometryFactory.h \
    GeometryFactory.h \
    Polycurve.h \
    GeometryComponent.h

SOURCES += \
    AbstractGeometry.cpp \
    Point.cpp \
    Segment.cpp \
    Ring.cpp \
    Polygon.cpp \
    Polyline.cpp \
    GeometryFactory.cpp \
    Polycurve.cpp \
    GeometryComponent.cpp

OTHER_FILES += Geometry.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
