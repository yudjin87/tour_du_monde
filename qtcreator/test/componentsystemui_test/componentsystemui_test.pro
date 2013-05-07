include (../test_shared.pri)
include (componentsystemui_test.pri)

QT      += gui
TARGET = componentsystemui_test

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/manual-test

LIBS += -L$${DESTDIR}/../bin -lFramework \
                             -lLogging \
                             -lUtils \
                             -lInteractivity \
                             -lComponentSystem \
                             -lComponentSystemUI \
