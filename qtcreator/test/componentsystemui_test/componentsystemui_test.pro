include (../test_shared.pri)
include (componentsystemui_test.pri)

QT += widgets
QT += xml xmlpatterns

TARGET = componentsystemui_test

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/manual-test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.ComponentSystemUI \

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
