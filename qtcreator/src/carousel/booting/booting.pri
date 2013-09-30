PROJECT_SOURCES = $$CPP_SOURCE_TREE/carousel/booting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/carousel/booting

SOURCES += \
    $$PROJECT_SOURCES/booting/BootloaderBase.cpp \
    $$PROJECT_SOURCES/booting/CarouselBootloader.cpp \

HEADERS += \
    $$PROJECT_HEADERS/booting/booting_global.h \
    $$PROJECT_HEADERS/booting/BootloaderBase.h \
    $$PROJECT_HEADERS/booting/CarouselBootloader.h \
    $$PROJECT_HEADERS/booting/IBootloader.h \

