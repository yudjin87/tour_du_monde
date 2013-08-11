include(../shared.pri)

QT       += core widgets

TARGET = org.carousel.demos.AddShapeOperation

TEMPLATE = lib

DEFINES += ADDSHAPEOPERATION_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lorg.carousel.Interactivity \
                           -lComponentSystem \
                           -lFramework \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.Carto \
                      -lorg.carousel.demos.Geodatabase

HEADERS += \
    AddShapeOperationComponent.h \
    addShapeOperation_api.h \
    AddShapeOperation.h \
    AddShapeOperationInteractiveExtension.h \
    AddShapesCommand.h

SOURCES += \
    AddShapeOperationComponent.cpp \
    AddShapeOperation.cpp \
    AddShapeOperationInteractiveExtension.cpp \
    AddShapesCommand.cpp

RESOURCES += \
    core.qrc

OTHER_FILES += \
    org.carousel.demos.AddShapeOperation.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
