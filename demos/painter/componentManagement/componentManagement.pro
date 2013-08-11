include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.ComponentManagement

TEMPLATE = lib

DEFINES += COMPONENTMANAGEMENT_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lorg.carousel.Interactivity \
                           -lorg.carousel.ComponentSystemUI \
                           -lComponentSystem \
                           -lFramework \

DESTDIR = $${DESTDIR}/lib

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
    org.carousel.demos.ComponentManagement.definition

RESOURCES += \
    ComponentManagement.qrc

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
