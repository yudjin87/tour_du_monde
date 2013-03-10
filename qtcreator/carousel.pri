# This is a settings file that contains a common used variables and
# instructions
#
#========================================================
#   +/carousel                     <= CAROUSEL_WD
#       +/demos
#       +/docs
#       +/include                  <= HPP_SOURCE_TREE
#       +/intermediate
#       +/mac64
#       +/msvc                     <= Source tree for the MSVC
#       +/qtcreator                <= IDE_SOURCE_TREE
#           +/carousel.pro
#           +/carousel_with_tests.pro
#       +/src                      <= CPP_SOURCE_TREE
#           +/booting              <= PROJECT_SOURCES
#           +/...
#       +/tests                    <= CPP_TESTS_TREE
#           +/booting_test         <= TEST_PROJECT_SOURCES
#           +/...
#       +/win32                    <= Binaries output (for different configurations and platforms)
#           +/debug
#              +/bin               <= BIN_OUTPUT_PATH
#           +/debug_static
#              +/bin
#              +/unittest          <= Static configurations have unittest applications
#           +/release
#           +/release_static
#========================================================
#

# Do not create symbol links
CONFIG += plugin

# Library information
#VERSION = 0.0.1.0
#QMAKE_TARGET_COMPANY = "Carousel"
#QMAKE_TARGET_DESCRIPTION = "Qt-based managed component library"
#QMAKE_TARGET_COPYRIGHT = "Copyright (c): 2011-2012 Carousel team"

IDE_SOURCE_TREE = $$PWD
CAROUSEL_WD  = $$PWD/..
CPP_SOURCE_TREE = $$CAROUSEL_WD/src
HPP_SOURCE_TREE = $$CAROUSEL_WD/include
CPP_TESTS_TREE = $$CAROUSEL_WD/tests

INCLUDEPATH += $$HPP_SOURCE_TREE

# Format binary output path:

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

DESTDIR         = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/bin

# Store intermedia stuff somewhere else
OBJECTS_DIR     = $${CAROUSEL_WD}/intermediate/obj/$${TARGET}
MOC_DIR         = $${CAROUSEL_WD}/intermediate/moc/$${TARGET}
RCC_DIR         = $${CAROUSEL_WD}/intermediate/rcc/$${TARGET}
UI_DIR          = $${CAROUSEL_WD}/intermediate/ui/$${TARGET}
UI_HEADERS_DIR  = $${CAROUSEL_WD}/intermediate/ui/$${TARGET}
UI_SOURCES_DIR  = $${CAROUSEL_WD}/intermediate/ui/$${TARGET}

#########################################################
# Compiler flags
#########################################################
# c++0x is skipped for the MSVC compiler.
!win32-msvc*:QMAKE_CXXFLAGS += -std=c++0x

#########################################################
# MSVC compiler shows this warning, but with virtual inheritance
# that problem is solved, so just disable it.
win32-msvc*:QMAKE_CXXFLAGS += /wd4250

#########################################################
# Copies the given files to the destination directory
defineTest(copyExtraFiles) {
    files = $$1

    for(FILE, files) {
        DDIR = $$DESTDIR

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}
