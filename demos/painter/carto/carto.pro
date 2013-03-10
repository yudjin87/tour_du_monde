include(../shared.pri)

QT       += gui

TEMPLATE = lib

TARGET = Carto

DEFINES += CARTO_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lUtils \
                           -lComponentSystem \
                           -lFramework \

DESTDIR = $${PAINTER_WD}/bin/externalSource

LIBS += -L$${DESTDIR} -lDisplay \

win32 {
    LIBS += -L$${DESTDIR} -lGeodatabase \
                          -lGeometry
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

OTHER_FILES += Carto.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
