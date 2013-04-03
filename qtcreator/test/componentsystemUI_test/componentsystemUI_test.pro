include (../test_shared.pri)
include (componentsystemUI_test.pri)

QT      += gui
TARGET = componentsystemUI_test

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/manual-test

LIBS += -L$${DESTDIR}/../bin -lLogging \
                             -lUtils \
                             -lComponentSystem \
                             -lComponentSystemUI \
