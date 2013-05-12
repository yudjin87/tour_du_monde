include (../test_shared.pri)
include (jsscripting_test.pri)

QT       += gui

TARGET = jsscripting_test

LIBS += -L$${DESTDIR}/../bin -lInteractivity \
                             -lComponentSystem \
                             -lFramework \
                             -lUtils \
                             -lLogging \
                             -lJsScripting \

