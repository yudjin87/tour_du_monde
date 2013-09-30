include (../../../carousel_props.pri)
include (undo.pri)

QT      += widgets
QT      += core
TEMPLATE = lib

TARGET = org.carousel.Undo

DEFINES += ORG_CAROUSEL_UNDO_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/undo

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lorg.carousel.Interactivity \
                      -lLogging \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
