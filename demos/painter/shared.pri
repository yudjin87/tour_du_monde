IDE_SOURCE_TREE = $$PWD
PAINTER_WD  = $$PWD
CPP_SOURCE_TREE = $$PAINTER_WD
HPP_SOURCE_TREE = $$PAINTER_WD

CAROUSEL_HPP_SOURCE_TREE = $$PWD/../../include

INCLUDEPATH += $$CAROUSEL_HPP_SOURCE_TREE
INCLUDEPATH += $$PAINTER_WD

CONFIG(dll, staticlib|dll):DEFINES += LIB_IMPORT

CONFIG += plugin

#########################################################
# c++0x is skipped for the MSVC compiler.
!win32-msvc*:QMAKE_CXXFLAGS += -std=c++0x

# Format binary output path:
win32-g*:BUILD_CONFIG=mingw
win32-msvc2008:BUILD_CONFIG=msvc09
win32-msvc2010:BUILD_CONFIG=msvc10
win32-msvc2012:BUILD_CONFIG=msvc11
macx:BUILD_CONFIG=clang
unix:BUILD_CONFIG=gnu

contains(QMAKE_HOST.arch, x86_64) {
    BUILD_CONFIG=$${BUILD_CONFIG}-x64
} else {
    BUILD_CONFIG=$${BUILD_CONFIG}-x32
}

CONFIG(release, debug|release) {
    BUILD_CONFIG=$${BUILD_CONFIG}-release
}
CONFIG(debug, debug|release) {
    BUILD_CONFIG=$${BUILD_CONFIG}-debug
}

static {# everything below takes effect with CONFIG+=static
    DEFINES += STATIC_BUILD
    BUILD_CONFIG=$${BUILD_CONFIG}-static
} else {
    DEFINES -= STATIC_BUILD
}

macx {
    # QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../PlugIns/$${PROVIDER}/
} else:linux-* {
    # do the rpath by hand since it's not possible to use ORIGIN in QMAKE_RPATHDIR
    QMAKE_RPATHDIR += \$\$ORIGIN/.
    QMAKE_RPATHDIR += \$\$ORIGIN/installedComponents
    IDE_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")
    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${IDE_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =
}

BIN_OUTPUT_PATH = product/$${BUILD_CONFIG}
CAROUSEL_BIN    = $${PAINTER_WD}/../../$${BIN_OUTPUT_PATH}/bin

BIN_OUTPUT_PATH = $${PAINTER_WD}/$${BIN_OUTPUT_PATH}
DESTDIR         = $${BIN_OUTPUT_PATH}/bin

# Store intermedia stuff somewhere else
OBJECTS_DIR     = $${PAINTER_WD}/intermediate/obj/$${TARGET}
MOC_DIR         = $${PAINTER_WD}/intermediate/moc/$${TARGET}
RCC_DIR         = $${PAINTER_WD}/intermediate/rcc/$${TARGET}
UI_DIR          = $${PAINTER_WD}/intermediate/ui/$${TARGET}
UI_HEADERS_DIR  = $${PAINTER_WD}/intermediate/ui/$${TARGET}
UI_SOURCES_DIR  = $${PAINTER_WD}/intermediate/ui/$${TARGET}

#########################################################
# MSVC compiler shows this warning, but with virtual inheritance
# that problem is solved, so just disable it.
win32-msvc*:QMAKE_CXXFLAGS += /wd4250

#########################################################
# Copies the given files to the destination directory
defineTest(copyExtraFiles) {
    files = $$1
    DDIR = $$2

    ABSOLUTE_PATH=$$PWD/

    win32-msvc*:DDIR ~= s,/,\\,g
    win32-msvc*:ABSOLUTE_PATH ~= s,/,\\,g

    # Create directory for copying
    win32-msvc* { # for Windows we also should check whether this directory exists
        QMAKE_POST_LINK += $$QMAKE_CHK_DIR_EXISTS $$quote($$DDIR) $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    } else {
        QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    for(FILE, files) {
        # Replace slashes in paths with backslashes for Windows
        win32-msvc*:FILE ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$ABSOLUTE_PATH$$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}
