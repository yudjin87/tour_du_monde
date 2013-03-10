include(../shared.pri)

QT       += core gui

TARGET = tableView

TEMPLATE = lib

DEFINES += TABLEVIEW_LIB_IMPORT

DESTDIR         = $${PAINTER_WD}/bin/components

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lcomponentsystem \
                               -linteractivity \
                               -lframework
}

HEADERS += \
    TableViewComponent.h \
    tableView_api.h \
    InteractiveExtension.h \
    ShapesWidget.h \
    ChildExtension.h \
    ShapesModel.h

SOURCES += \
    TableViewComponent.cpp \
    InteractiveExtension.cpp \
    ShapesWidget.cpp \
    ChildExtension.cpp \
    ShapesModel.cpp

FORMS += \
    ShapesWidget.ui
