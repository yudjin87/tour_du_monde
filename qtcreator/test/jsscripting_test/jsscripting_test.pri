TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/jsscripting_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/CarouselScriptEngineConfigurationDelegateTest.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeConfigurationDelegate.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeScriptCollection.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeScriptEngineFactory.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeScriptUnit.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentManager.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockOutputHandler.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockScriptExtensionComponent.cpp \
    $$TEST_PROJECT_SOURCES/main_jsscripting_test.cpp \
    $$TEST_PROJECT_SOURCES/ScriptCollectionTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptConsoleTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptEngineTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptingServiceTest.cpp \
    $$TEST_PROJECT_SOURCES/ScriptUnitTest.cpp \
    $$TEST_PROJECT_SOURCES/ServiceLocatorWrapperTest.cpp \
    $$TEST_PROJECT_SOURCES/SimpleCompleterTest.cpp \

HEADERS += \
    $$TEST_PROJECT_SOURCES/CarouselScriptEngineConfigurationDelegateTest.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeConfigurationDelegate.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeScriptCollection.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeScriptEngineFactory.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeScriptUnit.h \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentManager.h \
    $$TEST_PROJECT_SOURCES/fakes/MockOutputHandler.h \
    $$TEST_PROJECT_SOURCES/fakes/MockScriptExtensionComponent.h \
    $$TEST_PROJECT_SOURCES/ScriptCollectionTest.h \
    $$TEST_PROJECT_SOURCES/ScriptConsoleTest.h \
    $$TEST_PROJECT_SOURCES/ScriptEngineTest.h \
    $$TEST_PROJECT_SOURCES/ScriptingServiceTest.h \
    $$TEST_PROJECT_SOURCES/ScriptUnitTest.h \
    $$TEST_PROJECT_SOURCES/ServiceLocatorWrapperTest.h \
    $$TEST_PROJECT_SOURCES/SimpleCompleterTest.h \

OTHER_FILES += \
    $$TEST_PROJECT_SOURCES/TestScript.js \
    $$TEST_PROJECT_SOURCES/TestScript2.js \

