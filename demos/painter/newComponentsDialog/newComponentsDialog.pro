include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.NewComponentsDialog

TEMPLATE = lib

DEFINES += NEWCOMPONENTSDIALOG_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Interactivity \
                           -lorg.carousel.ComponentSystemUI \

DESTDIR = $${DESTDIR}/externalSource

FORMS +=

HEADERS += \
    newComponentsDialog_api.h \
    NewComponentsDialogComponent.h \
    NewDialog.h

SOURCES += \
    NewComponentsDialogComponent.cpp \
    NewDialog.cpp

OTHER_FILES += \
    org.carousel.demos.NewComponentsDialog.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
