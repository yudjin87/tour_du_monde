#version check qt
contains(QT_VERSION, ^4\\.[0-7]\\..*) {
    message("Cannot build carousel with Qt version $${QT_VERSION}.")
    error("Use at least Qt 4.8.")
}

TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += src \
           test
