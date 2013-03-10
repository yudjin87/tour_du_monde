include (../shared.pro)

TARGET = TestComponent1

TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystem_test_libs/testComponent1

SOURCES += \
        $$TEST_PROJECT_SOURCES/TestComponent1.cpp \

HEADERS += \
        $$TEST_PROJECT_SOURCES/TestComponent1.h\

OTHER_FILES += \
        $$TEST_PROJECT_SOURCES/TestComponent1.definition\

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/unittest/components

###############################################################################
# Copy test definitions to the output directory, near the test executable
copyExtraFiles($$OTHER_FILES)
