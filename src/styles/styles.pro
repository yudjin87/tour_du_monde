include(../shared.pri)

QT       += gui qml

TEMPLATE = lib

TARGET = org.carousel.demos.Styles

DEFINES += STYLES_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Carto \
                      -lorg.carousel.demos.Geometry \
                      -lorg.carousel.demos.CartoPersist \

HEADERS += \
    styles_api.h \
    StylesComponent.h \
#    commands/ChangeLayerStyleCommand.h \
    IFeatureLayerStyle.h \
    FeatureLayerStyle.h \
    ILayerStyleCollection.h \
    LayerStyleCollection.h \
    IStyleGalery.h \
    StyleGalery.h \
    FeatureLayerStylePersist.h

SOURCES += \
    StylesComponent.cpp \
#    commands/ChangeLayerStyleCommand.cpp \
    FeatureLayerStyle.cpp \
    LayerStyleCollection.cpp \
    StyleGalery.cpp \
    FeatureLayerStylePersist.cpp

OTHER_FILES += org.carousel.demos.Styles.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $${DESTDIR})

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.dll)
