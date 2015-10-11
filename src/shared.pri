TOUR_DU_MONDE_WD  = $$PWD/..
IDE_SOURCE_TREE = $$PWD
CPP_SOURCE_TREE = $$IDE_SOURCE_TREE
HPP_SOURCE_TREE = $$IDE_SOURCE_TREE

CAROUSEL_WD = $$TOUR_DU_MONDE_WD/../carousel
CAROUSEL_HPP_SOURCE_TREE = $$CAROUSEL_WD/include

INCLUDEPATH += $$CAROUSEL_HPP_SOURCE_TREE
INCLUDEPATH += $$HPP_SOURCE_TREE

CONFIG(dll, staticlib|dll):DEFINES += LIB_IMPORT

CONFIG += plugin

#########################################################
# c++11 is skipped for the MSVC compiler.
!win32-msvc*:QMAKE_CXXFLAGS += -std=c++11

# Format binary output path:
win32-g*:BUILD_CONFIG=mingw
win32-msvc*:BUILD_CONFIG=msvc
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

CAROUSEL_BIN    = $$CAROUSEL_WD/product/$${BUILD_CONFIG}/bin

BIN_OUTPUT_PATH = $${TOUR_DU_MONDE_WD}/product/$${BUILD_CONFIG}
DESTDIR         = $${BIN_OUTPUT_PATH}/bin

# Store intermedia stuff somewhere else
OBJECTS_DIR     = $${BIN_OUTPUT_PATH}/intermediate/obj/$${TARGET}
MOC_DIR         = $${BIN_OUTPUT_PATH}/intermediate/moc/$${TARGET}
RCC_DIR         = $${BIN_OUTPUT_PATH}/intermediate/rcc/$${TARGET}
UI_DIR          = $${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
UI_HEADERS_DIR  = $${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
UI_SOURCES_DIR  = $${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}

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

#########################################################
# Change %CONFIG% placeholder in the tour_du_monde.sh startup script
defineTest(prepareStartupScript) {
    file = $$1
    QMAKE_POST_LINK +=  sed -i 's/%CONFIG%/$${BUILD_CONFIG}/g' $$file
    export(QMAKE_POST_LINK)
}
