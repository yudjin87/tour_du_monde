include(../shared.pri)

QT       += core gui qml
QT       -= widgets

TEMPLATE = lib

TARGET = org.carousel.demos.Carto

DEFINES += CARTO_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.QmlScripting \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.Geodatabase \
                      -lorg.carousel.demos.Geometry

HEADERS += \
    carto_api.h \
    commands/AddShapesCommand.h \
    commands/RenameLayerCommand.h \
    commands/MoveLayerCommand.h \
    commands/RemoveLayerCommand.h \
    commands/ChangeLayerStyleCommand.h \
    commands/ChangeLegendClassCommand.h \
    layers/AbstractLayer.h \
    layers/FeatureLayer.h \
    layers/ILayerVisitor.h \
    layers/FeatureLayerDrawingTask.h \
    layers/LayerType.h \
    layers/ILayerCollection.h \
    layers/LayerCollection.h \
    legends/ILegendClass.h \
    legends/ILegendGroup.h \
    legends/LegendClass.h \
    legends/LegendGroup.h \
    renderers/IFeatureRenderer.h \
    renderers/SimpleRenderer.h \
    renderers/IFeatureRendererVisitor.h \
    renderers/CategorizedRenderer.h \
    renderers/RendererCategory.h \
    renderers/RendererCategoryCollection.h \
    renderers/IRendererCategory.h \
    renderers/IRendererCategoryCollection.h \
    renderers/RendererType.h \
    TourDuMondeDocument.h \
    TourDuMondeDocumentController.h \
    ITourDuMondeDocumentController.h \
    ITourDuMondeDocument.h \
    Map.h \
    CartoComponent.h \
    IMap.h \
    CartoScriptExtension.h \

SOURCES += \
    commands/AddShapesCommand.cpp \
    commands/RenameLayerCommand.cpp \
    commands/MoveLayerCommand.cpp \
    commands/RemoveLayerCommand.cpp \
    commands/ChangeLayerStyleCommand.cpp \
    commands/ChangeLegendClassCommand.cpp \
    layers/AbstractLayer.cpp \
    layers/FeatureLayer.cpp \
    layers/LayerType.cpp \
    layers/LayerCollection.cpp \
    layers/FeatureLayerDrawingTask.cpp \
    legends/LegendClass.cpp \
    legends/LegendGroup.cpp \
    renderers/SimpleRenderer.cpp \
    renderers/CategorizedRenderer.cpp \
    renderers/RendererCategory.cpp \
    renderers/RendererCategoryCollection.cpp \
    renderers/RendererType.cpp \
    Map.cpp \
    CartoComponent.cpp \
    TourDuMondeDocumentController.cpp \
    TourDuMondeDocument.cpp \
    CartoScriptExtension.cpp \

OTHER_FILES += org.carousel.demos.Carto.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $${DESTDIR})

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.dll)
