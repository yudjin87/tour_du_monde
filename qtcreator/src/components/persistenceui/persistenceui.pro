include (../../../carousel_props.pri)
include (persistenceui.pri)

QT += widgets

TEMPLATE = lib

TARGET = org.carousel.PersistenceUI

DEFINES += ORG_CAROUSEL_PERSISTENCEUI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/persistenceui

LIBS += -L$${DESTDIR} -lCarousel \
                      -lorg.carousel.Persistence \
                      -lorg.carousel.Interactivity \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
