include(../shared.pri)

QT       += core gui

TARGET = AddShapeOperation

TEMPLATE = lib

DEFINES += ADDSHAPEOPERATION_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lInteractivity \
                               -lFramework

    LIBS += -L$${DESTDIR} -lDisplay \
                          -lCarto \
                          -lGeometry
}

HEADERS += \
    AddShapeOperationComponent.h \
    addShapeOperation_api.h \
    AddShapeOperation.h \
    AddShapeOperationInteractiveExtension.h

SOURCES += \
    AddShapeOperationComponent.cpp \
    AddShapeOperation.cpp \
    AddShapeOperationInteractiveExtension.cpp

RESOURCES += \
    core.qrc

OTHER_FILES += \
    AddShapeOperation.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)