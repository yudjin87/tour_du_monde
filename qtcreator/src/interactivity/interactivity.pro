include (../../carousel.pri)
include (interactivity.pri)

QT       += gui
QT       += core
TEMPLATE = lib

TARGET = Interactivity

# avoid version in the target name for findows shared library:
!static:win32:TARGET_EXT = .dll

DEFINES += INTERACTIVITY_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/interactivity

LIBS += -L$${DESTDIR} -lComponentSystem \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
