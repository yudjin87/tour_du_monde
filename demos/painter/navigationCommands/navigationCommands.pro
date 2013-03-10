include(../shared.pri)

QT       += core gui

TARGET = NavigationCommands

TEMPLATE = lib

DEFINES += NAVIGATIONCOMMANDS_LIB_IMPORT

DESTDIR = $${PAINTER_WD}/bin/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lInteractivity \
                               -lFramework

    LIBS += -L$${DESTDIR} -lDisplay \
                          -lCarto \
                          -lGeometry
}

HEADERS += \
    NavigationCommandsComponent.h \
    navigationCommands_api.h \
    ZoomAllCommand.h \
    NavigationCommandsInteractiveExtension.h \
    ZoomInCommand.h \
    ZoomOutCommand.h \
    RectRubberBand.h \
    PanTool.h

SOURCES += \
    NavigationCommandsComponent.cpp \
    ZoomAllCommand.cpp \
    NavigationCommandsInteractiveExtension.cpp \
    ZoomInCommand.cpp \
    ZoomOutCommand.cpp \
    RectRubberBand.cpp \
    PanTool.cpp

RESOURCES += \
    navigation.qrc

OTHER_FILES += \
    NavigationCommands.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
