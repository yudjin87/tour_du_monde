include(../shared.pri)

QT       += gui

TEMPLATE = lib

TARGET = org.carousel.demos.Geodatabase

DEFINES += GEODATABASE_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lUtils \
                           -lComponentSystem \
                           -lFramework \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geometry \



HEADERS += \
    geodatabase_api.h \
    Feature.h \
    FeatureClass.h \
    IWorkspaceFactory.h \
    ShapeFileWorkspaceFactory.h \
    IWorkspace.h \
    IFeatureWorkspace.h \
    ShapeFileFeatureWorkspace.h \
    IDataset.h \
    IGeoDataset.h \
    IFeatureDataset.h \
    ShapeFileFeatureDataset.h \
    IShapeFileReader.h \
    ShapeFileReader.h \
    IFeatureClass.h \
    IFeature.h \
    GeodatabaseComponent.h \
    IShapeFileWorkspaceFactory.h \
    ISpatialFilter.h \
    SpatialFilter.h \
    GDBScriptExtension.h

SOURCES += \
    Feature.cpp \
    FeatureClass.cpp \
    ShapeFileWorkspaceFactory.cpp \
    ShapeFileFeatureWorkspace.cpp \
    ShapeFileFeatureDataset.cpp \
    ShapeFileReader.cpp \
    GeodatabaseComponent.cpp \
    SpatialFilter.cpp \
    GDBScriptExtension.cpp


OTHER_FILES += org.carousel.demos.Geodatabase.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
