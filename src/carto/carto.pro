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
    TourDuMondeDocument.h \
    TourDuMondeDocumentController.h \
    ITourDuMondeDocumentController.h \
    ITourDuMondeDocument.h \
    AbstractLayer.h \
    FeatureLayer.h \
    Map.h \
    CartoComponent.h \
    IMap.h \
    ILayerVisitor.h \
    CartoScriptExtension.h \
    FeatureLayerDrawingTask.h \
    IFeatureRenderer.h \
    ILegendClass.h \
    ILegendGroup.h \
    LegendClass.h \
    commands/AddShapesCommand.h \
    commands/RenameLayerCommand.h \
    commands/MoveLayerCommand.h \
    commands/RemoveLayerCommand.h \
    LegendGroup.h \
    SimpleRenderer.h \
    IFeatureRendererVisitor.h \
    commands/ChangeLayerStyleCommand.h \
    CategorizedRenderer.h \
    RendererCategory.h \
    RendererCategoryCollection.h \
    IRendererCategory.h \
    IRendererCategoryCollection.h \
    LayerType.h \
    RendererType.h \
    commands/ChangeLegendClassCommand.h \
    ILayerCollection.h \
    LayerCollection.h

SOURCES += \
    AbstractLayer.cpp \
    FeatureLayer.cpp \
    Map.cpp \
    CartoComponent.cpp \
    TourDuMondeDocumentController.cpp \
    TourDuMondeDocument.cpp \
    CartoScriptExtension.cpp \
    FeatureLayerDrawingTask.cpp \
    LegendClass.cpp \
    commands/AddShapesCommand.cpp \
    commands/RenameLayerCommand.cpp \
    commands/MoveLayerCommand.cpp \
    commands/RemoveLayerCommand.cpp \
    LegendGroup.cpp \
    SimpleRenderer.cpp \
    commands/ChangeLayerStyleCommand.cpp \
    CategorizedRenderer.cpp \
    RendererCategory.cpp \
    RendererCategoryCollection.cpp \
    LayerType.cpp \
    RendererType.cpp \
    commands/ChangeLegendClassCommand.cpp \
    LayerCollection.cpp

OTHER_FILES += org.carousel.demos.Carto.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $${DESTDIR})

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.dll)
