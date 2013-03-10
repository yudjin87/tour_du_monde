include (../test_shared.pri)
include (logging_test.pri)

TARGET = logging_test

LIBS += -L$${DESTDIR}/../bin -lLogging

