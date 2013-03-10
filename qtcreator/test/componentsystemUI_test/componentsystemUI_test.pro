include (../../carousel.pri)
include (componentsystemUI.test.pri)

QT       -= gui
QT       += testlib
QT       += core

TEMPLATE = app

TARGET = test_ComponentSystemUI

CONFIG   += console
CONFIG   -= app_bundle

LIBS += -L$${DESTDIR} -lComponentSystemUI \
                      -lUtils

DESTDIR         = $${CAROUSEL_WD}/bin/tests
