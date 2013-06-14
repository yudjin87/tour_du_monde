include(../shared.pri)

QT       += gui

TEMPLATE = lib

TARGET = org.carousel.demos.Carto

DEFINES += CARTO_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lUtils \
                           -lComponentSystem \
                           -lFramework \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \

win32 {
    LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geodatabase \
                          -lorg.carousel.demos.Geometry
}

HEADERS += \
    carto_api.h \
    AbstractLayer.h \
    FeatureLayer.h \
    Map.h \
    CartoComponent.h

SOURCES += \
    AbstractLayer.cpp \
    FeatureLayer.cpp \
    Map.cpp \
    CartoComponent.cpp

OTHER_FILES += org.carousel.demos.Carto.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
