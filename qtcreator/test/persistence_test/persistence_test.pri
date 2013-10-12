TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/persistence_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/CarouselPersistenceDelegateTest.cpp \
    $$TEST_PROJECT_SOURCES/fakes/JustComponent.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockPersistExtension.cpp \
    $$TEST_PROJECT_SOURCES/fakes/PersistComponent.cpp \
    $$TEST_PROJECT_SOURCES/main_persistence_test.cpp \

HEADERS += \
    $$TEST_PROJECT_SOURCES/CarouselPersistenceDelegateTest.h \
    $$TEST_PROJECT_SOURCES/fakes/JustComponent.h \
    $$TEST_PROJECT_SOURCES/fakes/MockPersistExtension.h \
    $$TEST_PROJECT_SOURCES/fakes/PersistComponent.h \

