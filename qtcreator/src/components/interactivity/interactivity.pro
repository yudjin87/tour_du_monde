include (../../../carousel_props.pri)
include (interactivity.pri)

QT       += widgets
QT       += core
TEMPLATE = lib

TARGET = Interactivity

DEFINES += INTERACTIVITY_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/interactivity

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lLogging \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)