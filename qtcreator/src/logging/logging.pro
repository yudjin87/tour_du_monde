include (../../carousel.pri)
include (logging.pri)

QT      -= gui
TEMPLATE = lib

TARGET = Logging

# avoid version in the target name for findows shared library:
!static:win32:TARGET_EXT = .dll

DEFINES += LOGGING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/logging
