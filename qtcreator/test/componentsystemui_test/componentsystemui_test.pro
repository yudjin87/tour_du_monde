include (../test_shared.pri)
include (componentsystemui_test.pri)

QT += widgets
QT += xml xmlpatterns

CONFIG += windeployqt
QMAKE_POST_LINKCONFIG += windeployqt

TARGET = componentsystemui_test

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/manual-test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.ComponentSystemUI \
