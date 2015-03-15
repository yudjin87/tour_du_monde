include(../shared.pri)

QT       += core widgets gui

TARGET = org.carousel.demos.CartoUI

TEMPLATE = lib

DEFINES += CARTO_UI_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource


LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.Carto \
                      -lorg.carousel.demos.Geometry


HEADERS += \
    cartoUI_api.h \
    CartoUIComponent.h \
    CartoUIInteractiveExtension.h \
    FeatureLayerDelegate.h \
    AddShapeOperation.h \
    FeatureLayerPropertiesWidget.h \
    LayerPropertyWidgetCreator.h \
    LayerTreeModel.h \
    FeatureLayerItem.h \
    SymbolItem.h \
    LayerItemCreator.h \
    LayerTreeView.h

SOURCES += \
    CartoUIComponent.cpp \
    CartoUIInteractiveExtension.cpp \
    FeatureLayerDelegate.cpp \
    AddShapeOperation.cpp \
    FeatureLayerPropertiesWidget.cpp \
    LayerPropertyWidgetCreator.cpp \
    LayerTreeModel.cpp \
    FeatureLayerItem.cpp \
    SymbolItem.cpp \
    LayerItemCreator.cpp \
    LayerTreeView.cpp

FORMS += \
    FeatureLayerPropertiesWidget.ui

OTHER_FILES += \
    org.carousel.demos.CartoUI.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)


RESOURCES += \
    cartoUI.qrc
