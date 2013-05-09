PROJECT_SOURCES = $$CPP_SOURCE_TREE/logging
PROJECT_HEADERS = $$HPP_SOURCE_TREE/logging

SOURCES += \
    $$PROJECT_SOURCES/TextLogger.cpp \
    $$PROJECT_SOURCES/LoggerFacade.cpp \
    $$PROJECT_SOURCES/NullLogger.cpp \

HEADERS += \
    $$PROJECT_HEADERS/logging_global.h \
    $$PROJECT_HEADERS/TextLogger.h \
    $$PROJECT_HEADERS/LoggerFacade.h \
    $$PROJECT_HEADERS/NullLogger.h \

