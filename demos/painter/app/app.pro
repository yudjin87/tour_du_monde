include(../shared.pri)

QT       += core widgets

win32:TARGET = painter
unix:TARGET = painter.bin

TEMPLATE = app

DESTDIR = $${BIN_OUTPUT_PATH}/bin

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \
                           -lorg.carousel.JsScripting \
                           -lorg.carousel.JsScriptingUI \
                           -lorg.carousel.ComponentSystemUI \
                           -lorg.carousel.Undo \
                           -lorg.carousel.Persistence \
                           -lorg.carousel.PersistenceUI \

SOURCES += \
    main.cpp\
    MainWindow.cpp \
    Bootloader.cpp \
    PainterApplication.cpp \
    LoggerEngine.cpp \

HEADERS  += \
    MainWindow.h \
    Bootloader.h \
    PainterApplication.h \
    LoggerEngine.h \

FORMS += \
    MainWindow.ui


SHAPES += buckinghamshire/README
SHAPES += buckinghamshire/buildings.shp
SHAPES += buckinghamshire/landuse.shp
SHAPES += buckinghamshire/natural.shp
SHAPES += buckinghamshire/railways.shp
SHAPES += buckinghamshire/waterways.shp
SHAPES += buckinghamshire/world.shp

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
