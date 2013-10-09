include (../../../carousel_props.pri)
include (persistence.pri)

QT -= widgets gui
QT += core

TEMPLATE = lib

TARGET = org.carousel.Persistence

DEFINES += ORG_CAROUSEL_PERSISTENCE_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/persistence

LIBS += -L$${DESTDIR} -lCarousel

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
