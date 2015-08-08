include(../shared.pri)

QT       += core widgets

win32:TARGET = tour_du_monde
unix:TARGET = tour_du_monde.bin

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
    TourDuMondeApplication.cpp \
    LoggerEngine.cpp \

HEADERS  += \
    MainWindow.h \
    Bootloader.h \
    TourDuMondeApplication.h \
    LoggerEngine.h \

FORMS += \
    MainWindow.ui

SHAPES += boeblingen/buildings.cpg
SHAPES += boeblingen/buildings.dbf
SHAPES += boeblingen/buildings.prj
SHAPES += boeblingen/buildings.shp
SHAPES += boeblingen/buildings.shx
SHAPES += boeblingen/landuse.cpg
SHAPES += boeblingen/landuse.dbf
SHAPES += boeblingen/landuse.prj
SHAPES += boeblingen/landuse.shp
SHAPES += boeblingen/landuse.shx
SHAPES += boeblingen/natural.cpg
SHAPES += boeblingen/natural.dbf
SHAPES += boeblingen/natural.prj
SHAPES += boeblingen/natural.shp
SHAPES += boeblingen/natural.shx
SHAPES += boeblingen/places.cpg
SHAPES += boeblingen/places.dbf
SHAPES += boeblingen/places.prj
SHAPES += boeblingen/places.shp
SHAPES += boeblingen/places.shx
SHAPES += boeblingen/points.cpg
SHAPES += boeblingen/points.dbf
SHAPES += boeblingen/points.prj
SHAPES += boeblingen/points.shp
SHAPES += boeblingen/points.shx
SHAPES += boeblingen/railways.cpg
SHAPES += boeblingen/railways.dbf
SHAPES += boeblingen/railways.prj
SHAPES += boeblingen/railways.shp
SHAPES += boeblingen/railways.shx
SHAPES += boeblingen/README.txt
SHAPES += boeblingen/roads.cpg
SHAPES += boeblingen/roads.dbf
SHAPES += boeblingen/roads.prj
SHAPES += boeblingen/roads.shp
SHAPES += boeblingen/roads.shx
SHAPES += boeblingen/waterways.cpg
SHAPES += boeblingen/waterways.dbf
SHAPES += boeblingen/waterways.prj
SHAPES += boeblingen/waterways.shp
SHAPES += boeblingen/waterways.shx
SHAPES += boeblingen/world.shp

BOEBLINGEN_PROJECT += demo_project.proj
START_UP = tour_du_monde.sh

SCRIPTS += scripts/startup.js
SCRIPTS += scripts/components.js
SCRIPTS += scripts/loadLayer.js
SCRIPTS += scripts/navigation.js
SCRIPTS += scripts/uiManipulations.js
SCRIPTS += scripts/scripting.js

OTHER_FILES += \
    $${START_UP} \
    $${SHAPES} \
    $${SCRIPTS} \
    $${BOEBLINGEN_PROJECT} \

###############################################################################
# Copy demo data files to the output dir
copyExtraFiles($$SHAPES, $${DESTDIR}/data)
copyExtraFiles($$SCRIPTS, $${DESTDIR}/scripts)
copyExtraFiles($$BOEBLINGEN_PROJECT, $${DESTDIR}/)
unix:copyExtraFiles($$START_UP, $${DESTDIR}/)
unix:prepareStartupScript($${DESTDIR}/$$START_UP)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($${DESTDIR}/$${TARGET}.exe)
