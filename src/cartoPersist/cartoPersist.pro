include(../shared.pri)

TEMPLATE = lib

TARGET = org.carousel.demos.CartoPersist

DEFINES += CARTO_PERSIST_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Persistence \
                           -lorg.carousel.demos.Geodatabase \
                           -lorg.carousel.demos.Display \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Carto \

HEADERS += \
    cartoPersist_api.h \
    CartoPersistComponent.h \
    CartoPersistExtension.h \
    TourDuMondeDocumentPersist.h \
    MapPersist.h \
    ILayerPersist.h \
    FeatureLayerPersist.h \
    LayerPersistCreator.h \
    FeatureClassPersist.h \
    IFeatureRendererPersist.h \
    SimpleRendererPersist.h \
    FeatureRendererPersistCreator.h \
    CategorizedRendererPersist.h \
    LegendGroupPersist.h \
    LegendClassPersist.h \
    ISymbolPersist.h \
    SymbolPersistCreator.h \
    SimpleFillSymbolPersist.h \
    SimpleLineSymbolPersist.h \
    SimpleMarkerSymbolPersist.h \
    PictureMarkerSymbolPersist.h \
    RendererCategoryCollectionPersist.h \
    RendererCategoryPersist.h \
    PictureFillSymbolPersist.h \
    GradientFillSymbolPersist.h

SOURCES += \
    CartoPersistComponent.cpp \
    CartoPersistExtension.cpp \
    TourDuMondeDocumentPersist.cpp \
    MapPersist.cpp \
    FeatureLayerPersist.cpp \
    LayerPersistCreator.cpp \
    FeatureClassPersist.cpp \
    SimpleRendererPersist.cpp \
    FeatureRendererPersistCreator.cpp \
    CategorizedRendererPersist.cpp \
    LegendGroupPersist.cpp \
    LegendClassPersist.cpp \
    SymbolPersistCreator.cpp \
    SimpleFillSymbolPersist.cpp \
    SimpleLineSymbolPersist.cpp \
    SimpleMarkerSymbolPersist.cpp \
    PictureMarkerSymbolPersist.cpp \
    RendererCategoryCollectionPersist.cpp \
    RendererCategoryPersist.cpp \
    PictureFillSymbolPersist.cpp \
    GradientFillSymbolPersist.cpp

OTHER_FILES += org.carousel.demos.CartoPersist.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $${DESTDIR})

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.dll)
