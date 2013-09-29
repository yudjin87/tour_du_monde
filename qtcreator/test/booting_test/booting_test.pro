include (../test_shared.pri)
include (booting_test.pri)

QT -= widgets gui

TARGET = booting_test

LIBS += -L$${DESTDIR}/../bin -lBooting \
                             -lLogging \
                             -lComponentSystem \
                             -lUtils \
