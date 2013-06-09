include (../../../carousel_props.pri)
include (componentsystemui.pri)

QT      += widgets
QT      += core
TEMPLATE = lib

TARGET = ComponentSystemUI

DEFINES += COMPONENTSYSTEMUI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/componentsystemui

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lInteractivity \
                      -lFramework \
                      -lUtils \
                      -lLogging \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
