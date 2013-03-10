include (../shared.pro)

TARGET = exportCreateFuncOnly

TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystem_test_libs/exportCreateFuncOnly

SOURCES += \
        $$TEST_PROJECT_SOURCES/ExportCreateFuncOnly.cpp \

HEADERS += \
        $$TEST_PROJECT_SOURCES/ExportCreateFuncOnly.h\
