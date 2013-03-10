TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/utils_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/fakes/MockServiceLocator.cpp \
    $$TEST_PROJECT_SOURCES/fakes/Services.cpp \
    $$TEST_PROJECT_SOURCES/main_utils_test.cpp \
    $$TEST_PROJECT_SOURCES/ObservableListTest.cpp \
    $$TEST_PROJECT_SOURCES/ServiceLocatorTest.cpp \

HEADERS += \
    $$TEST_PROJECT_SOURCES/fakes/MockListObserver.h \
    $$TEST_PROJECT_SOURCES/fakes/MockServiceLocator.h \
    $$TEST_PROJECT_SOURCES/fakes/Services.h \
    $$TEST_PROJECT_SOURCES/ObservableListTest.h \
    $$TEST_PROJECT_SOURCES/ServiceLocatorTest.h \

