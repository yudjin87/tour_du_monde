PROJECT_SOURCES = $$CPP_SOURCE_TREE/carousel/logging
PROJECT_HEADERS = $$HPP_SOURCE_TREE/carousel/logging

SOURCES += \
    $$PROJECT_SOURCES/LoggerFacade.cpp \
    $$PROJECT_SOURCES/NullLogger.cpp \
    $$PROJECT_SOURCES/TextLogger.cpp \

HEADERS += \
    $$PROJECT_HEADERS/ILoggerEngine.h \
    $$PROJECT_HEADERS/ILoggerEngineCreator.h \
    $$PROJECT_HEADERS/LoggerFacade.h \
    $$PROJECT_HEADERS/logging_global.h \
    $$PROJECT_HEADERS/NullLogger.h \
    $$PROJECT_HEADERS/TextLogger.h \

