include (../../../carousel_props.pri)
include (jsscripting.pri)

QT      += widgets
QT      += core
TEMPLATE = lib

TARGET = JsScripting

DEFINES += JSSCRIPTING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/jsscripting

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lFramework \
                      -lInteractivity \
                      -lLogging \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
