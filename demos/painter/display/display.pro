include(../shared.pri)

QT       += core widgets

TARGET = Display

TEMPLATE = lib

DEFINES += DISPLAY_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lInteractivity \

DESTDIR = $${DESTDIR}/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lFramework \

    LIBS += -L$${DESTDIR} -lGeometry \
}

HEADERS += \
    display_api.h \
    DisplayComponent.h \
    IAppDisplay.h \
    SimpleDisplay.h \
    Throttle.h \
    FeatureRenderer.h

SOURCES += \
    DisplayComponent.cpp \
    SimpleDisplay.cpp \
    Throttle.cpp \
    FeatureRenderer.cpp

FORMS +=

OTHER_FILES += Display.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
