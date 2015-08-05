include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.NavigationOperations

TEMPLATE = lib

DEFINES += NAVIGATIONOPERATIONS_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.Carto \
                      -lorg.carousel.demos.Geometry


HEADERS += \
    NavigationOperationsComponent.h \
    navigationOperations_api.h \
    ZoomAllOperation.h \
    NavigationOperationsInteractiveExtension.h \
    ZoomOutOperation.h \
    PanTool.h \
    ZoomInTool.h \

SOURCES += \
    NavigationOperationsComponent.cpp \
    ZoomAllOperation.cpp \
    NavigationOperationsInteractiveExtension.cpp \
    ZoomOutOperation.cpp \
    PanTool.cpp \
    ZoomInTool.cpp \

RESOURCES += \
    navigation.qrc

OTHER_FILES += \
    org.carousel.demos.NavigationOperations.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
