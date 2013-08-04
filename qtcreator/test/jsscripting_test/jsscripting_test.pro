include (../test_shared.pri)
include (jsscripting_test.pri)

QT       += widgets
QT      += script

TARGET = jsscripting_test

LIBS += -L$${DESTDIR}/../bin -lorg.carousel.Interactivity \
                             -lComponentSystem \
                             -lFramework \
                             -lUtils \
                             -lLogging \
                             -lorg.carousel.JsScripting \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)
