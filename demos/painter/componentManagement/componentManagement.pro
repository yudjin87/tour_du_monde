include(../shared.pri)

QT       += core gui

TARGET = ComponentManagement

TEMPLATE = lib

DEFINES += COMPONENTMANAGEMENT_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lInteractivity \

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lComponentSystemUI \
                               -lFramework \
}

DESTDIR = $${DESTDIR}/components

FORMS +=

HEADERS += \
    componentManagement_api.h \
    ComponentManagementComponent.h \
    ComponentManagementInteractiveExtension.h \
    InstallComponentsOperation.h \
    ShowComponentsOperation.h

SOURCES += \
    ComponentManagementComponent.cpp \
    ComponentManagementInteractiveExtension.cpp \
    InstallComponentsOperation.cpp \
    ShowComponentsOperation.cpp

OTHER_FILES += \
    ComponentManagement.definition

RESOURCES += \
    ComponentManagement.qrc

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
