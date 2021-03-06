include(../shared.pri)

QT       += core widgets gui qml

TARGET = org.carousel.demos.CartoUI

TEMPLATE = lib

DEFINES += CARTO_UI_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource


LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \
                           -lorg.carousel.QmlScripting \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.DisplayWidgets \
                      -lorg.carousel.demos.Carto \
                      -lorg.carousel.demos.Geometry \
                      -lorg.carousel.demos.Geodatabase


HEADERS += \
    cartoUI_api.h \
    RectRubberBand.h \
    CartoUIComponent.h \
    CartoUIInteractiveExtension.h \
    FeatureLayerDelegate.h \
    AddShapeOperation.h \
    FeatureLayerPropertiesWidget.h \
    LayerPropertyWidgetCreator.h \
    LayerTreeModel.h \
    FeatureLayerItem.h \
    LayerItemCreator.h \
    LayerTreeView.h \
    FeatureClassModel.h \
    FeatureClassTableView.h \
    LegendClassItem.h \
    FeatureRendererWidgetCreator.h \
    SimpleRendererWidget.h \
    FeatureRendererWidget.h \
    CategorizedRendererWidget.h \
    RendererCategoryItem.h \
    RendererCategoryCollectionModel.h \
    DefaultNavigationHandler.h \
    CoordsTracker.h \
    MapView.h \
    CartoUIScriptExtension.h \

SOURCES += \
    CartoUIComponent.cpp \
    RectRubberBand.cpp \
    CartoUIInteractiveExtension.cpp \
    FeatureLayerDelegate.cpp \
    AddShapeOperation.cpp \
    FeatureLayerPropertiesWidget.cpp \
    LayerPropertyWidgetCreator.cpp \
    LayerTreeModel.cpp \
    FeatureLayerItem.cpp \
    LayerItemCreator.cpp \
    LayerTreeView.cpp \
    FeatureClassModel.cpp \
    FeatureClassTableView.cpp \
    LegendClassItem.cpp \
    FeatureRendererWidgetCreator.cpp \
    SimpleRendererWidget.cpp \
    FeatureRendererWidget.cpp \
    CategorizedRendererWidget.cpp \
    RendererCategoryItem.cpp \
    RendererCategoryCollectionModel.cpp \
    DefaultNavigationHandler.cpp \
    CoordsTracker.cpp \
    MapView.cpp \
    CartoUIScriptExtension.cpp

FORMS += \
    FeatureLayerPropertiesWidget.ui \
    SimpleRendererWidget.ui \
    CategorizedRendererWidget.ui \
    MapView.ui

OTHER_FILES += \
    org.carousel.demos.CartoUI.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $${DESTDIR})


RESOURCES += \
    cartoUI.qrc

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.dll)
