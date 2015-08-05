include(../shared.pri)

QT       += script sql

TEMPLATE = lib

TARGET = org.carousel.demos.Geodatabase

DEFINES += GEODATABASE_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.JsScripting \

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
    IShapeFileReader.h \
    ShapeFileReader.h \
    ShapeType.h \
    IFeatureClass.h \
    IFeature.h \
    IRecord.h \
    GeodatabaseComponent.h \
    IShapeFileWorkspaceFactory.h \
    ISpatialFilter.h \
    SpatialFilter.h \
    GDBScriptExtension.h \
    GeometryFactory.h \
    BinaryReader.h \
    FeatureClassLoader.h \
    IFeatureClassLoader.h \
    IFields.h \
    IField.h \
    Field.h \
    Fields.h \
    Record.h \
    IFieldsEdit.h \
    ITable.h \
    Table.h \
    winutils.h \
    ColumnClassificator.h

SOURCES += \
    Feature.cpp \
    FeatureClass.cpp \
    ShapeFileWorkspaceFactory.cpp \
    ShapeFileFeatureWorkspace.cpp \
    ShapeFileReader.cpp \
    GeodatabaseComponent.cpp \
    SpatialFilter.cpp \
    GDBScriptExtension.cpp \
    GeometryFactory.cpp \
    BinaryReader.cpp \
    ShapeType.cpp \
    FeatureClassLoader.cpp \
    Field.cpp \
    Fields.cpp \
    Record.cpp \
    Table.cpp \
    winutils.cpp \
    ColumnClassificator.cpp

OTHER_FILES += org.carousel.demos.Geodatabase.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
