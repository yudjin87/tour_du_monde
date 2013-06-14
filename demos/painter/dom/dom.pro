include(../shared.pri)

QT       -= gui

TEMPLATE = lib

TARGET = org.carousel.demos.Dom

DEFINES += DOM_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lFramework

    LIBS += -L$${DESTDIR} -lorg.carousel.demos.Carto
}

# Sources:
HEADERS += \
    dom_api.h \
    DomComponent.h \
    PainterDocument.h \
    PainterDocumentController.h \
    IPainterDocumentController.h \
    IPainterDocument.h \
    IShape.h

SOURCES += \
    PainterDocumentController.cpp \
    DomComponent.cpp \
    PainterDocument.cpp

OTHER_FILES += org.carousel.demos.Dom.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
