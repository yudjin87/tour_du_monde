include (../../../carousel_props.pri)
include (jsscriptingui.pri)

QT      += widgets
QT      += core
QT      += script

TEMPLATE = lib

TARGET = org.carousel.JsScriptingUI

DEFINES += ORG_CAROUSEL_JSSCRIPTINGUI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/jsscriptingui

LIBS += -L$${DESTDIR} -lCarousel \
                      -lorg.carousel.JsScripting \
                      -lorg.carousel.Interactivity \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
