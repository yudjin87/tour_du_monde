TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/jsscripting_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/main_jsscripting_test.cpp \
    $$TEST_PROJECT_SOURCES/ScriptConsoleTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptConsoleViewTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptEngineTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptingServiceTest.cpp \
    $$TEST_PROJECT_SOURCES/ServiceLocatorWrapperTest.cpp \

HEADERS += \
    $$TEST_PROJECT_SOURCES/ScriptConsoleTest.h \
    $$TEST_PROJECT_SOURCES/ScriptConsoleViewTest.h \
    $$TEST_PROJECT_SOURCES/ScriptEngineTest.h \
    $$TEST_PROJECT_SOURCES/ScriptingServiceTest.h \
    $$TEST_PROJECT_SOURCES/ServiceLocatorWrapperTest.h \

