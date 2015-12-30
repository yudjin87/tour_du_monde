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
    legends/LegendGroupPersist.h \
    legends/LegendClassPersist.h \
    layers/ILayerPersist.h \
    layers/FeatureLayerPersist.h \
    layers/LayerPersistCreator.h \
    renderers/IFeatureRendererPersist.h \
    renderers/SimpleRendererPersist.h \
    renderers/FeatureRendererPersistCreator.h \
    renderers/CategorizedRendererPersist.h \
    renderers/RendererCategoryCollectionPersist.h \
    renderers/RendererCategoryPersist.h \
    symbols/ISymbolPersist.h \
    symbols/SymbolPersistCreator.h \
    symbols/SimpleFillSymbolPersist.h \
    symbols/SimpleLineSymbolPersist.h \
    symbols/SimpleMarkerSymbolPersist.h \
    symbols/PictureMarkerSymbolPersist.h \
    symbols/PictureFillSymbolPersist.h \
    symbols/GradientFillSymbolPersist.h \
    symbols/SimpleTextSymbolPersist.h \
    CartoPersistComponent.h \
    CartoPersistExtension.h \
    TourDuMondeDocumentPersist.h \
    MapPersist.h \
    FeatureClassPersist.h \

SOURCES += \
    legends/LegendGroupPersist.cpp \
    legends/LegendClassPersist.cpp \
    layers/FeatureLayerPersist.cpp \
    layers/LayerPersistCreator.cpp \
    renderers/SimpleRendererPersist.cpp \
    renderers/FeatureRendererPersistCreator.cpp \
    renderers/CategorizedRendererPersist.cpp \
    renderers/RendererCategoryCollectionPersist.cpp \
    renderers/RendererCategoryPersist.cpp \
    symbols/SymbolPersistCreator.cpp \
    symbols/SimpleFillSymbolPersist.cpp \
    symbols/SimpleLineSymbolPersist.cpp \
    symbols/SimpleMarkerSymbolPersist.cpp \
    symbols/PictureMarkerSymbolPersist.cpp \
    symbols/PictureFillSymbolPersist.cpp \
    symbols/GradientFillSymbolPersist.cpp \
    symbols/SimpleTextSymbolPersist.cpp \
    CartoPersistComponent.cpp \
    CartoPersistExtension.cpp \
    TourDuMondeDocumentPersist.cpp \
    MapPersist.cpp \
    FeatureClassPersist.cpp \

OTHER_FILES += org.carousel.demos.CartoPersist.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $${DESTDIR})

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.dll)
