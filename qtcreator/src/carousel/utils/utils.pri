PROJECT_SOURCES = $$CPP_SOURCE_TREE/carousel/utils
PROJECT_HEADERS = $$HPP_SOURCE_TREE/carousel/utils

SOURCES += \
    $$PROJECT_SOURCES/FileUtils.cpp \
    $$PROJECT_SOURCES/ServiceLocator.cpp \

HEADERS += \
    $$PROJECT_HEADERS/FileUtils.h \
    $$PROJECT_HEADERS/IServiceLocator.h \
    $$PROJECT_HEADERS/ListDictionary.h \
    $$PROJECT_HEADERS/ObservableList.h \
    $$PROJECT_HEADERS/ServiceLocator.h \
    $$PROJECT_HEADERS/TypeObjectsMap.h \
    $$PROJECT_HEADERS/utils_global.h \

