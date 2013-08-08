include(../shared.pri)

QT       += core

TEMPLATE = lib

TARGET = org.carousel.demos.Geometry

DEFINES += GEOMETRY_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lUtils \
                           -lComponentSystem \

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
    GeometryComponent.h \
    GeometryScriptExtension.h

SOURCES += \
    AbstractGeometry.cpp \
    Point.cpp \
    Segment.cpp \
    Ring.cpp \
    Polygon.cpp \
    Polyline.cpp \
    GeometryFactory.cpp \
    Polycurve.cpp \
    GeometryComponent.cpp \
    GeometryScriptExtension.cpp

OTHER_FILES += org.carousel.demos.Geometry.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
