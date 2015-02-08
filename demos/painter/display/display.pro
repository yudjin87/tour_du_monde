include(../shared.pri)

QT       += core widgets script

TARGET = org.carousel.demos.Display

TEMPLATE = lib

DEFINES += DISPLAY_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \
                           -lorg.carousel.JsScripting \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geometry \

HEADERS += \
    display_api.h \
    DisplayComponent.h \
    RectRubberBand.h \
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
    DisplayScriptExtension.h \
    ThreadSafeQueue.h \
    IDrawingTask.h \
    RenderThread.h \
    MultithreadDisplay.h \
    StartDrawingTask.h \
    UpdateTask.h

SOURCES += \
    RectRubberBand.cpp \
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
    DisplayScriptExtension.cpp \
    ThreadSafeQueue.cpp \
    RenderThread.cpp \
    MultithreadDisplay.cpp \
    StartDrawingTask.cpp \
    UpdateTask.cpp

FORMS +=

OTHER_FILES += org.carousel.demos.Display.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
