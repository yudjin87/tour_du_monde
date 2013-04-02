include (../../carousel.pri)
include (componentsystemUI.pri)

QT      += gui
QT      += core
TEMPLATE = lib

TARGET = ComponentSystemUI

DEFINES += COMPONENTSYSTEM_UI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/componentsystemUI

LIBS += -L$${DESTDIR} -lComponentSystem \
