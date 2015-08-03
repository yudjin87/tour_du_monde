include (../test_shared.pri)
include (jsscripting_test.pri)

QT      -= widgets
QT      += script gui

TARGET = jsscripting_test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.JsScripting \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
