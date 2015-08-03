include (../test_shared.pri)
include (jsscriptingui_test.pri)

QT      += widgets
QT      += script

TARGET = jsscriptingui_test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.JsScripting \
                             -lorg.carousel.JsScriptingUI \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
