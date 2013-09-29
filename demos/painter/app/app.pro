include(../shared.pri)

QT       += core widgets

win32:TARGET = painter
unix:TARGET = painter.bin

TEMPLATE = app

DESTDIR = $${BIN_OUTPUT_PATH}/bin

LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                           -lBooting \
                           -lFramework \
                           -lUtils \
                           -lLogging \
                           -lorg.carousel.Interactivity \
                           -lorg.carousel.JsScripting \
                           -lorg.carousel.JsScriptingUI \
                           -lorg.carousel.ComponentSystemUI \
                           -lorg.carousel.Undo \

SOURCES += \
    main.cpp\
    MainWindow.cpp \
    Bootloader.cpp \
    PainterApplication.cpp

HEADERS  += \
    MainWindow.h \
    Bootloader.h \
    PainterApplication.h

FORMS += \
    MainWindow.ui


SHAPES += buckinghamshire/README
SHAPES += buckinghamshire/buildings.shp
SHAPES += buckinghamshire/landuse.shp
SHAPES += buckinghamshire/natural.shp
SHAPES += buckinghamshire/railways.shp
SHAPES += buckinghamshire/waterways.shp

START_UP = painter.sh

SCRIPTS += scripts/startup.js
SCRIPTS += scripts/changeColor.js
SCRIPTS += scripts/components.js
SCRIPTS += scripts/loadLayer.js
SCRIPTS += scripts/navigation.js
SCRIPTS += scripts/uiManipulations.js
SCRIPTS += scripts/scripting.js

OTHER_FILES += \
    $${START_UP} \
    $${SHAPES} \
    $${SCRIPTS} \

###############################################################################
# Copy demo data files to the output dir
copyExtraFiles($$SHAPES, $$DESTDIR/data)
copyExtraFiles($$SCRIPTS, $$DESTDIR/scripts)
unix:copyExtraFiles($$START_UP, $$DESTDIR/)
unix:prepareStartupScript($$DESTDIR/$$START_UP)
