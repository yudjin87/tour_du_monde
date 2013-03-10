include (../../carousel.pri)
include (framework.pri)

QT      += gui
TEMPLATE = lib

TARGET = Framework

# avoid version in the target name for findows shared library:
!static:win32:TARGET_EXT = .dll

DEFINES += FRAMEWORK_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/framework
