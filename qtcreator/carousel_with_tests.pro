#version check qt
contains(QT_VERSION, ^4\\..*) {
    message("Cannot build carousel with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.0")
}

TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += src \
           test \

include(doc/doc.pri)
