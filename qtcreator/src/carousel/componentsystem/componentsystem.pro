include (../../../carousel_props.pri)
include (componentsystem.pri)

QT      -= widgets gui
QT      += xml
TEMPLATE = lib

TARGET = ComponentSystem

DEFINES += COMPONENTSYSTEM_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/carousel/componentsystem

LIBS += -L$${DESTDIR} -lUtils \
                      -lLogging \
