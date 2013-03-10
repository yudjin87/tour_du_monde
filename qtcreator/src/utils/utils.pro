include (../../carousel.pri)
include (utils.pri)

QT      -= gui
TEMPLATE = lib

TARGET = Utils

# avoid version in the target name for findows shared library:
!static:win32:TARGET_EXT = .dll

DEFINES += UTILS_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/utils
