include (../../carousel.pri)
include (framework.pri)

QT      += widgets
TEMPLATE = lib

TARGET = Framework

DEFINES += FRAMEWORK_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/framework

LIBS += -L$${DESTDIR} -lComponentSystem
