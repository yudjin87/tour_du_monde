include (../test_shared.pri)
include (booting_test.pri)

QT -= widgets gui
QT += xml

TARGET = booting_test

LIBS += -L$${DESTDIR}/../bin -lCarousel
