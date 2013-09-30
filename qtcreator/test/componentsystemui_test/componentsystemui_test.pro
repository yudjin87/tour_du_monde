include (../test_shared.pri)
include (componentsystemui_test.pri)

QT      += widgets
TARGET = componentsystemui_test

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/manual-test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.Undo \
                             -lorg.carousel.ComponentSystemUI \
