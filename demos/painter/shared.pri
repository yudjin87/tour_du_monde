IDE_SOURCE_TREE = $$PWD
PAINTER_WD  = $$PWD
CPP_SOURCE_TREE = $$PAINTER_WD
HPP_SOURCE_TREE = $$PAINTER_WD

CAROUSEL_HPP_SOURCE_TREE = $$PWD/../../include

INCLUDEPATH += $$CAROUSEL_HPP_SOURCE_TREE
INCLUDEPATH += $$PAINTER_WD

CONFIG(dll, staticlib|dll):DEFINES += LIB_IMPORT

DESTDIR         = $${PAINTER_WD}/bin
# Store intermedia stuff somewhere else
OBJECTS_DIR     = $${PAINTER_WD}/intermediate/obj/$${TARGET}
MOC_DIR         = $${PAINTER_WD}/intermediate/moc/$${TARGET}
RCC_DIR         = $${PAINTER_WD}/intermediate/rcc/$${TARGET}
UI_DIR          = $${PAINTER_WD}/intermediate/ui/$${TARGET}
UI_HEADERS_DIR  = $${PAINTER_WD}/intermediate/ui/$${TARGET}
UI_SOURCES_DIR  = $${PAINTER_WD}/intermediate/ui/$${TARGET}

#CONFIG += plugin
#########################################################
# c++0x is skipped for the MSVC compiler.
!win32-msvc*:QMAKE_CXXFLAGS += -std=c++0x

#########################################################
# Format binary path for the carousel outputs:
win32-g*:BIN_OUTPUT_PATH=mingw
win32-msvc*:BIN_OUTPUT_PATH=win
macx:BIN_OUTPUT_PATH=mac
unix:BIN_OUTPUT_PATH=linux


contains(QMAKE_HOST.arch, x86_64) {
    BIN_OUTPUT_PATH=$${BIN_OUTPUT_PATH}32
} else {
    BIN_OUTPUT_PATH=$${BIN_OUTPUT_PATH}32
}

CONFIG(release, debug|release) {
    BIN_OUTPUT_PATH=$${BIN_OUTPUT_PATH}/release
}
CONFIG(debug, debug|release) {
    BIN_OUTPUT_PATH=$${BIN_OUTPUT_PATH}/debug
}

static {# everything below takes effect with CONFIG+=static
    DEFINES += STATIC_BUILD
    BIN_OUTPUT_PATH=$${BIN_OUTPUT_PATH}_static
} else {
    DEFINES -= STATIC_BUILD
}

CAROUSEL_BIN = $${PAINTER_WD}/../../$${BIN_OUTPUT_PATH}/bin

#########################################################
# MSVC compiler shows this warning, but with virtual inheritance
# that problem is solved, so just disable it.
win32-msvc*:QMAKE_CXXFLAGS += /wd4250

#########################################################
# Copies the given files to the destination directory
defineTest(copyExtraFiles) {
    files = $$1
    DDIR = $$2

    win32-msvc*:DDIR ~= s,/,\\,g

    # Create directory for copying
    win32-msvc* { # for Windows we also should check whether this directory exists
        QMAKE_POST_LINK += $$QMAKE_CHK_DIR_EXISTS $$quote($$DDIR) $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    } else {
        QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    for(FILE, files) {
        # Replace slashes in paths with backslashes for Windows
        win32-msvc*:FILE ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}
