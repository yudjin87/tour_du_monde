include (../../../carousel_props.pri)
include (componentsystemui.pri)

QT      += widgets
QT      += core
TEMPLATE = lib

TARGET = org.carousel.ComponentSystemUI

DEFINES += ORG_CAROUSEL_COMPONENTSYSTEMUI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/componentsystemui

LIBS += -L$${DESTDIR} -lCarousel \
                      -lorg.carousel.Interactivity \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
