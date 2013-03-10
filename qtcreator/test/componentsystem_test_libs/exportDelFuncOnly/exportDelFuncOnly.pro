include (../shared.pro)

TARGET = exportDelFuncOnly

TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystem_test_libs/exportDelFuncOnly

SOURCES += \
        $$TEST_PROJECT_SOURCES/ExportDelFuncOnly.cpp \

HEADERS += \
        $$TEST_PROJECT_SOURCES/ExportDelFuncOnly.h\
