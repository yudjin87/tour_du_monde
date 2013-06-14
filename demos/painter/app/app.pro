include(../shared.pri)

QT       += core widgets

TARGET = painter

TEMPLATE = app

DESTDIR = $${BIN_OUTPUT_PATH}/bin

LIBS += -L$${DESTDIR}/components -lorg.carousel.demos.ComponentManagement

LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                           -lBooting \
                           -lFramework \
                           -lUtils \
                           -lLogging \
                           -lorg.carousel.Interactivity \
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

OTHER_FILES += \
    buckinghamshire/README \
    buckinghamshire/buildings.shp \
    buckinghamshire/landuse.shp \
    buckinghamshire/natural.shp \
    buckinghamshire/railways.shp \
    buckinghamshire/waterways.shp

###############################################################################
# Copy demo data files to the output dir
copyExtraFiles($$OTHER_FILES, $$DESTDIR/data)
