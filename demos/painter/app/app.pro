include(../shared.pri)

QT       += core gui

TARGET = painter

TEMPLATE = app

DESTDIR = $${BIN_OUTPUT_PATH}/bin

LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                           -lBooting \
                           -lFramework \
                           -lUtils \
                           -lLogging \
                           -lInteractivity

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
