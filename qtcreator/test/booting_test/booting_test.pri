TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/booting_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/BaseBootloaderTest.cpp \
    $$TEST_PROJECT_SOURCES/CarouselBootloaderTest.cpp \
    $$TEST_PROJECT_SOURCES/fakes/BootloaderMock.cpp \
    $$TEST_PROJECT_SOURCES/fakes/CarouselBootloader_ComponentManagerFixture.cpp \
    $$TEST_PROJECT_SOURCES/fakes/CarouselBootloaderMock.cpp \
    $$TEST_PROJECT_SOURCES/fakes/CarouselBootloaderProviderMock.cpp \
    $$TEST_PROJECT_SOURCES/main_booting_test.cpp \

HEADERS += \
    $$TEST_PROJECT_SOURCES/BaseBootloaderTest.h \
    $$TEST_PROJECT_SOURCES/CarouselBootloaderTest.h \
    $$TEST_PROJECT_SOURCES/fakes/BootloaderMock.h \
    $$TEST_PROJECT_SOURCES/fakes/CarouselBootloader_ComponentManagerFixture.h \
    $$TEST_PROJECT_SOURCES/fakes/CarouselBootloaderMock.h \
    $$TEST_PROJECT_SOURCES/fakes/CarouselBootloaderProviderMock.h \

