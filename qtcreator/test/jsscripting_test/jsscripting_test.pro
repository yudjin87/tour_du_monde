include (../test_shared.pri)
include (jsscripting_test.pri)

QT       += widgets

TARGET = jsscripting_test

LIBS += -L$${DESTDIR}/../bin -lorg.carousel.Interactivity \
                             -lComponentSystem \
                             -lFramework \
                             -lUtils \
                             -lLogging \
                             -lorg.carousel.JsScripting \

