include (../../carousel.pri)
include (interactivityUI.test.pri)

QT       += gui
QT       += testlib
QT       += core

TEMPLATE = app

TARGET = test_Interactivity

CONFIG   += console
CONFIG   -= app_bundle

LIBS += -L$${DESTDIR} -lInteractivity \
                      -lComponentSystem \
                      -lFramework \
                      -lUtils \

DESTDIR         = $${CAROUSEL_WD}/bin/tests
