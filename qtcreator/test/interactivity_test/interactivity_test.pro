include (../test_shared.pri)
include (interactivity_test.pri)

QT       += widgets gui

TARGET = interactivity_test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
