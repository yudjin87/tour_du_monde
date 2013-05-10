include (../../carousel.pri)
include (componentsystemui.pri)

QT      += gui
QT      += core
TEMPLATE = lib

TARGET = ComponentSystemUI

DEFINES += COMPONENTSYSTEMUI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/componentsystemui

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lInteractivity \
                      -lFramework \
                      -lUtils \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
