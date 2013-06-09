include (../../carousel.pri)
include (booting.pri)

QT      += widgets

TEMPLATE = lib

TARGET = Booting

DEFINES += BOOTING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/booting

LIBS += -L$${DESTDIR} -lLogging \
                      -lComponentSystem \
                      -lUtils
