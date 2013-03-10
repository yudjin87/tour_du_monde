include (../../carousel.pri)
include (componentsystem.pri)

QT      -= gui
QT      += xml
TEMPLATE = lib

TARGET = ComponentSystem

# avoid version in the target name for findows shared library:
!static:win32:TARGET_EXT = .dll

DEFINES += COMPONENTSYSTEM_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/componentsystem

LIBS += -L$${DESTDIR} -lUtils \
                      -lLogging \
