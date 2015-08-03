include (../test_shared.pri)
include (logging_test.pri)

TARGET = logging_test

LIBS += -L$${DESTDIR}/../bin -lCarousel

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)

