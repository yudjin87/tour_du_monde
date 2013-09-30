include (../../../carousel_props.pri)
include (interactivity.pri)

QT       += widgets
QT       += core
TEMPLATE = lib

TARGET = org.carousel.Interactivity

DEFINES += ORG_CAROUSEL_INTERACTIVITY_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/interactivity

LIBS += -L$${DESTDIR} -lCarousel

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
