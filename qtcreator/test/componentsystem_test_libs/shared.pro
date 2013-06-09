include (../../carousel_props.pri)

QT       -= widgets
TEMPLATE = lib

CONFIG += dll

# avoid version in the target name for findows shared library:
win32:TARGET_EXT = .dll

# This stuff is needed for the CoomponentSystem static lib
LIBS += -L$${DESTDIR} -lLogging \
                      -lComponentSystem \
                      -lUtils \

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/unittest/libs
