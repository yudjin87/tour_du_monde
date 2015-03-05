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
    LayersTreeModel.h \
    FeatureLayerDelegate.h \
    AddShapeOperation.h \
    FeatureLayerPropertiesWidget.h \
    LayersListView.h \
    LayerPropertyWidgetCreator.h

SOURCES += \
    CartoUIComponent.cpp \
    CartoUIInteractiveExtension.cpp \
    LayersTreeModel.cpp \
    FeatureLayerDelegate.cpp \
    AddShapeOperation.cpp \
    FeatureLayerPropertiesWidget.cpp \
    LayersListView.cpp \
    LayerPropertyWidgetCreator.cpp

FORMS += \
    FeatureLayerPropertiesWidget.ui

OTHER_FILES += \
    org.carousel.demos.CartoUI.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)


RESOURCES += \
    cartoUI.qrc
