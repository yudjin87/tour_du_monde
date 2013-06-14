include (../../../carousel_props.pri)
include (jsscripting.pri)

QT      += widgets
QT      += core
TEMPLATE = lib

TARGET = org.carousel.JsScripting

DEFINES += ORG_CAROUSEL_JSSCRIPTING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/jsscripting

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lFramework \
                      -lorg.carousel.Interactivity \
                      -lLogging \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
