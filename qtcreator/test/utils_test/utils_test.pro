include (../test_shared.pri)
include (utils_test.pri)

TARGET = utils_test

LIBS += -L$${DESTDIR}/../bin -lCarousel

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
