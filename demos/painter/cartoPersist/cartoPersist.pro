include(../shared.pri)

TEMPLATE = lib

TARGET = org.carousel.demos.CartoPersist

DEFINES += CARTO_PERSIST_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.Persistence \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Carto \

HEADERS += \
    cartoPersist_api.h \
    CartoPersistComponent.h \
    CartoPersistExtension.h \

SOURCES += \
    CartoPersistComponent.cpp \
    CartoPersistExtension.cpp \

OTHER_FILES += org.carousel.demos.CartoPersist.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
