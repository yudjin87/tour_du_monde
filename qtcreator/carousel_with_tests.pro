#version check qt
contains(QT_VERSION, ^5\\.[0-2]\\..*) {
    message("Cannot build Qt Creator with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.3.")
}

TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += src \
           test \

include(doc/doc.pri)
