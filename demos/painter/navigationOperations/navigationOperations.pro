include(../shared.pri)

QT       += core widgets

TARGET = NavigationOperations

TEMPLATE = lib

DEFINES += NAVIGATIONOPERATIONS_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lInteractivity \
                               -lFramework

    LIBS += -L$${DESTDIR} -lDisplay \
                          -lCarto \
                          -lGeometry
}

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
    NavigationOperations.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
