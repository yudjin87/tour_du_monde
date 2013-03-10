include (../test_shared.pri)
include (interactivity_test.pri)

QT       += gui

TARGET = interactivity_test

LIBS += -L$${DESTDIR}/../bin -lInteractivity \
                             -lComponentSystem \
                             -lFramework \
                             -lUtils \
                             -lLogging \
