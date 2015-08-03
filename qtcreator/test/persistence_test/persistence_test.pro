include (../test_shared.pri)
include (persistence_test.pri)

TARGET = persistence_test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Persistence \

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
