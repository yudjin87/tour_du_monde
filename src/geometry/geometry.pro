include(../shared.pri)

QT       += core script

TEMPLATE = lib

TARGET = org.carousel.demos.Geometry

DEFINES += GEOMETRY_LIB_IMPORT


DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.JsScripting \

HEADERS += \
    geometry_api.h \
    IGeometry.h \
    Point.h \
    Segment.h \
    Ring.h \
    Polygon.h \
    GeometryType.h \
    Polyline.h \
    Polycurve.h \
    GeometryComponent.h \
    GeometryScriptExtension.h \
    Curve.h \
    Path.h \
    Line.h \
    GeometryBase.h

SOURCES += \
    Point.cpp \
    Segment.cpp \
    Ring.cpp \
    Polygon.cpp \
    Polyline.cpp \
    Polycurve.cpp \
    GeometryComponent.cpp \
    GeometryScriptExtension.cpp \
    Curve.cpp \
    Path.cpp \
    Line.cpp \
    GeometryBase.cpp

OTHER_FILES += org.carousel.demos.Geometry.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
