include (../test_shared.pri)
include (componentsystem_test.pri)

QT      += xml
TARGET = componentsystem_test

LIBS += -L$${DESTDIR}/../bin -lLogging \
                             -lUtils \
                             -lComponentSystem \

