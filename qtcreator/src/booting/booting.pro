include (../../carousel.pri)
include (booting.pri)

QT      += gui

TEMPLATE = lib

TARGET = Booting

# avoid version in the target name for findows shared library:
!static:win32:TARGET_EXT = .dll

DEFINES += BOOTING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/booting

LIBS += -L$${DESTDIR} -lLogging \
                      -lComponentSystem \
                      -lUtils
