include (../carousel.pri)

QT       -= widgets
QT       += testlib
QT       += core

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/unittest
