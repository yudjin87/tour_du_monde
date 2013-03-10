include (../carousel.pri)
include (interactivityUI.pri)

QT       += gui
QT       += core
TEMPLATE = lib

TARGET = InteractivityUI

DEFINES += INTERACTIVITY_LIB_IMPORT

INCLUDEPATH += $$HPP_SOURCE_TREE/interactivityUI
