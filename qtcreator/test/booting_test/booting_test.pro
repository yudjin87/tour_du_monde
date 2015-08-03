include (../test_shared.pri)
include (booting_test.pri)

QT -= widgets gui
QT += xml

TARGET = booting_test

LIBS += -L$${DESTDIR}/../bin -lCarousel

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
