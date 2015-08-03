include (../test_shared.pri)
include (componentsystem_test.pri)

QT      += xml
TARGET = componentsystem_test

LIBS += -L$${DESTDIR}/../bin -lCarousel

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
