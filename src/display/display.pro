include(../shared.pri)

QT       += core widgets script

TARGET = org.carousel.demos.Display

TEMPLATE = lib

DEFINES += DISPLAY_LIB_IMPORT

ROOT_DIR = $${DESTDIR}

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
    UpdateTask.h \
    CoordsTracker.h \
    SymbolThumbnail.h \
    ISymbolVisitor.h \
    PictureMarkerSymbol.h \
    SymbolType.h \
    PictureFillSymbol.h

SOURCES += \
    RectRubberBand.cpp \
    DisplayComponent.cpp \
    SimpleDisplay.cpp \
    Throttle.cpp \
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
    UpdateTask.cpp \
    CoordsTracker.cpp \
    SymbolThumbnail.cpp \
    PictureMarkerSymbol.cpp \
    SymbolType.cpp \
    PictureFillSymbol.cpp

MARKERS += \
    markers/Education/* \
    markers/EntertainmentArtsCulture/* \
    markers/Healthcare/* \
    markers/Historic/* \
    markers/Leisure/* \
    markers/Others/* \
    markers/Shop/* \
    markers/Sustenance/* \
    markers/Tourism/* \
    markers/Transportation/* \

BRUSHES += \
    brushes/Landuse/* \
    brushes/Natural/* \

DEFINITION = org.carousel.demos.Display.definition

OTHER_FILES += $$DEFINITION \
               $$MARKERS

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$DEFINITION, $$DESTDIR)
copyExtraFiles($$MARKERS, $$ROOT_DIR/markers)
copyExtraFiles($$BRUSHES, $$ROOT_DIR/brushes)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
