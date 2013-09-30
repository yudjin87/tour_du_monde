include (../../carousel_props.pri)
include (carousel.pri)

QT -= widgets gui
QT += xml xmlpatterns

TEMPLATE = lib

TARGET = Carousel

DEFINES += CAROUSEL_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/carousel
