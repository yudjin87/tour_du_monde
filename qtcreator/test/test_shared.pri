include (../carousel_props.pri)

QT       -= widgets
QT       += testlib
QT       += core

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/unittest

INCLUDEPATH += $$HPP_SOURCE_TREE/carousel \
               $$HPP_SOURCE_TREE/components
