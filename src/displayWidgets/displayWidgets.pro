include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.DisplayWidgets

TEMPLATE = lib

DEFINES += DISPLAY_WIDGETS_LIB_IMPORT

ROOT_DIR = $${DESTDIR}

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geometry \
                      -lorg.carousel.demos.Display \

HEADERS += \
    displayWidgets_api.h \
    DisplayWidgetsComponent.h \
    SimpleLineSymbolWidget.h \
    SymbolWidgetCreator.h \
    ColorPickerButtont.h \
    SymbolWidget.h \
    SimpleFillSymbolWidget.h \
    SimpleMarkerSymbolWidget.h \
    PictureMarkerSymbolWidget.h \
    SymbolEditorWidget.h \
    MarkerSymbolEditorWidget.h \
    LineSymbolEditorWidget.h \
    FillSymbolEditorWidget.h \
    PictureFillSymbolWidget.h

SOURCES += \
    DisplayWidgetsComponent.cpp \
    SimpleLineSymbolWidget.cpp \
    SymbolWidgetCreator.cpp \
    ColorPickerButtont.cpp \
    SymbolWidget.cpp \
    SimpleFillSymbolWidget.cpp \
    SimpleMarkerSymbolWidget.cpp \
    PictureMarkerSymbolWidget.cpp \
    SymbolEditorWidget.cpp \
    MarkerSymbolEditorWidget.cpp \
    LineSymbolEditorWidget.cpp \
    FillSymbolEditorWidget.cpp \
    PictureFillSymbolWidget.cpp

FORMS += \
    SimpleLineSymbolWidget.ui \
    SimpleFillSymbolWidget.ui \
    SimpleMarkerSymbolWidget.ui \
    PictureMarkerSymbolWidget.ui \
    SymbolEditorWidget.ui \
    PictureFillSymbolWidget.ui

DEFINITION = org.carousel.demos.DisplayWidgets.definition

OTHER_FILES += $$DEFINITION \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$DEFINITION, $$DESTDIR)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
