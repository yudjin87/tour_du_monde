include(../shared.pri)

QT       += core gui

TARGET = AddShapeCommand

TEMPLATE = lib

DEFINES += ADDSHAPECOMMAND_LIB_IMPORT

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
    AddShapeCommandComponent.h \
    addShapeCommand_api.h \
    AddShapeCommand.h \
    AddShapeCommandInteractiveExtension.h

SOURCES += \
    AddShapeCommandComponent.cpp \
    AddShapeCommand.cpp \
    AddShapeCommandInteractiveExtension.cpp

RESOURCES += \
    core.qrc

OTHER_FILES += \
    AddShapeCommand.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
