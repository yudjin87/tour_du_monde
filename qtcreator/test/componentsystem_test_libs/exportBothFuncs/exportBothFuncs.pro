include (../shared.pro)

TARGET = exportBothFuncs

TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystem_test_libs/exportBothFuncs

SOURCES += \
        $$TEST_PROJECT_SOURCES/ExportBothFuncs.cpp \

HEADERS += \
        $$TEST_PROJECT_SOURCES/ExportBothFuncs.h\
