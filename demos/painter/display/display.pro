include(../shared.pri)

QT       += core widgets

TARGET = Display

TEMPLATE = lib

DEFINES += DISPLAY_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lInteractivity \

DESTDIR = $${DESTDIR}/installedComponents/Display

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lFramework \

    LIBS += -L$${DESTDIR} -lGeometry \
}

HEADERS += \
    display_api.h \
    DisplayComponent.h \
    IDisplay.h \
    SimpleDisplay.h \
    Throttle.h \
    FeatureRenderer.h \
    ISymbol.h \
    SymbolBase.h \
    MarkerSymbol.h \
    SimpleMarkerSymbol.h \
    LineSymbol.h \
    SimpleLineSymbol.h

SOURCES += \
    DisplayComponent.cpp \
    SimpleDisplay.cpp \
    Throttle.cpp \
    FeatureRenderer.cpp \
    SymbolBase.cpp \
    MarkerSymbol.cpp \
    SimpleMarkerSymbol.cpp \
    LineSymbol.cpp \
    SimpleLineSymbol.cpp

FORMS +=

OTHER_FILES += Display.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
