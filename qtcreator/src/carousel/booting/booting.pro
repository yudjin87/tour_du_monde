include (../../../carousel_props.pri)
include (booting.pri)

QT -= widgets gui

TEMPLATE = lib

TARGET = Booting

DEFINES += BOOTING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/carousel/booting

LIBS += -L$${DESTDIR} -lLogging \
                      -lComponentSystem \
                      -lUtils
