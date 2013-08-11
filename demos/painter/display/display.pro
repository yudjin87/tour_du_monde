include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.Display

TEMPLATE = lib

DEFINES += DISPLAY_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lorg.carousel.Interactivity \

DESTDIR = $${DESTDIR}/externalSource
#DESTDIR = $${DESTDIR}/installedComponents/org.carousel.demos.Display

LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                           -lFramework

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geometry \

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
    SimpleLineSymbol.h \
    FillSymbol.h \
    SimpleFillSymbol.h \
    DisplayTransformation.h \
    DisplayScriptExtension.h

SOURCES += \
    DisplayComponent.cpp \
    SimpleDisplay.cpp \
    Throttle.cpp \
    FeatureRenderer.cpp \
    SymbolBase.cpp \
    MarkerSymbol.cpp \
    SimpleMarkerSymbol.cpp \
    LineSymbol.cpp \
    SimpleLineSymbol.cpp \
    FillSymbol.cpp \
    SimpleFillSymbol.cpp \
    DisplayTransformation.cpp \
    DisplayScriptExtension.cpp

FORMS +=

OTHER_FILES += org.carousel.demos.Display.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
