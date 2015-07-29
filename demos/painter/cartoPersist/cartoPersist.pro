include(../shared.pri)

TEMPLATE = lib

TARGET = org.carousel.demos.CartoPersist

DEFINES += CARTO_PERSIST_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Persistence \
                      -lorg.carousel.demos.Geodatabase \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Carto \

HEADERS += \
    cartoPersist_api.h \
    CartoPersistComponent.h \
    CartoPersistExtension.h \
    PainterDocumentPersist.h \
    MapPersist.h \
    ILayerPersist.h \
    FeatureLayerPersist.h \
    LayerPersistCreator.h \
    FeatureClassPersist.h \
    IFeatureRendererPersist.h \
    SimpleRendererPersist.h \
    FeatureRendererPersistCreator.h \
    CategorizedRendererPersist.h

SOURCES += \
    CartoPersistComponent.cpp \
    CartoPersistExtension.cpp \
    PainterDocumentPersist.cpp \
    MapPersist.cpp \
    FeatureLayerPersist.cpp \
    LayerPersistCreator.cpp \
    FeatureClassPersist.cpp \
    SimpleRendererPersist.cpp \
    FeatureRendererPersistCreator.cpp \
    CategorizedRendererPersist.cpp

OTHER_FILES += org.carousel.demos.CartoPersist.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)