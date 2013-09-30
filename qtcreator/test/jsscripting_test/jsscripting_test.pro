include (../test_shared.pri)
include (jsscripting_test.pri)

QT      -= widgets
QT      += script gui

TARGET = jsscripting_test

LIBS += -L$${DESTDIR}/../bin -lComponentSystem \
                             -lUtils \
                             -lLogging \
                             -lorg.carousel.JsScripting \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)
