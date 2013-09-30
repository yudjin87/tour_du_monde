PROJECT_SOURCES = $$CPP_SOURCE_TREE/carousel/utils
PROJECT_HEADERS = $$HPP_SOURCE_TREE/carousel/utils

SOURCES += \
    $$PROJECT_SOURCES/utils/FileUtils.cpp \
    $$PROJECT_SOURCES/utils/ServiceLocator.cpp \

HEADERS += \
    $$PROJECT_HEADERS/utils/FileUtils.h \
    $$PROJECT_HEADERS/utils/IServiceLocator.h \
    $$PROJECT_HEADERS/utils/ListDictionary.h \
    $$PROJECT_HEADERS/utils/ObservableList.h \
    $$PROJECT_HEADERS/utils/ServiceLocator.h \
    $$PROJECT_HEADERS/utils/TypeObjectsMap.h \
    $$PROJECT_HEADERS/utils/utils_global.h \

