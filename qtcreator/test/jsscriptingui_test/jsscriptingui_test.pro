include (../test_shared.pri)
include (jsscriptingui_test.pri)

QT      += widgets
QT      += script

TARGET = jsscriptingui_test

LIBS += -L$${DESTDIR}/../bin -lorg.carousel.Interactivity \
                             -lComponentSystem \
                             -lUtils \
                             -lLogging \
                             -lorg.carousel.JsScripting \
                             -lorg.carousel.JsScriptingUI \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)
