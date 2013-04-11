include (../../carousel.pri)
include (componentsystemui.pri)

QT      += gui
QT      += core
TEMPLATE = lib

TARGET = ComponentSystemUI

DEFINES += COMPONENTSYSTEM_UI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/componentsystemui

LIBS += -L$${DESTDIR} -lComponentSystem \
