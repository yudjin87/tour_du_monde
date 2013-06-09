PROJECT_SOURCES = $$CPP_SOURCE_TREE/carousel/booting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/carousel/booting

SOURCES += \
    $$PROJECT_SOURCES/BootloaderBase.cpp \
    $$PROJECT_SOURCES/CarouselBootloader.cpp \

HEADERS += \
    $$PROJECT_HEADERS/booting_global.h \
    $$PROJECT_HEADERS/BootloaderBase.h \
    $$PROJECT_HEADERS/CarouselBootloader.h \
    $$PROJECT_HEADERS/IBootloader.h \

