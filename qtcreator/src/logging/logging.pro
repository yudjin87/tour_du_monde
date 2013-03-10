include (../../carousel.pri)
include (logging.pri)

QT      -= gui
TEMPLATE = lib

TARGET = Logging

DEFINES += LOGGING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/logging
