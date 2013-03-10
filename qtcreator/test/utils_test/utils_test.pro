include (../test_shared.pri)
include (utils_test.pri)

TARGET = utils_test

LIBS += -L$${DESTDIR}/../bin -lUtils
