include (../shared.pro)

TARGET = TestComponent2

TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystem_test_libs/testComponent2

SOURCES += \
        $$TEST_PROJECT_SOURCES/TestComponent2.cpp \

HEADERS += \
        $$TEST_PROJECT_SOURCES/TestComponent2.h\

OTHER_FILES += \
        $$TEST_PROJECT_SOURCES/TestComponent2.definition\

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/unittest/components

###############################################################################
# Copy test definitions to the output directory, near the test executable
copyExtraFiles($$OTHER_FILES)
