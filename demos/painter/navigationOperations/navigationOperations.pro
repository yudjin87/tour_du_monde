include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.NavigationOperations

TEMPLATE = lib

DEFINES += NAVIGATIONOPERATIONS_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                           -lFramework \
                           -lorg.carousel.Interactivity \
                           -lorg.carousel.Undo \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.Carto \
                      -lorg.carousel.demos.Geometry


HEADERS += \
    NavigationOperationsComponent.h \
    navigationOperations_api.h \
    ZoomAllOperation.h \
    NavigationOperationsInteractiveExtension.h \
    ZoomInOperation.h \
    ZoomOutOperation.h \
    RectRubberBand.h \
    PanTool.h

SOURCES += \
    NavigationOperationsComponent.cpp \
    ZoomAllOperation.cpp \
    NavigationOperationsInteractiveExtension.cpp \
    ZoomInOperation.cpp \
    ZoomOutOperation.cpp \
    RectRubberBand.cpp \
    PanTool.cpp

RESOURCES += \
    navigation.qrc

OTHER_FILES += \
    org.carousel.demos.NavigationOperations.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
