PROJECT_SOURCES = $$CPP_SOURCE_TREE/jsscripting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/jsscripting

HEADERS += \
    $$PROJECT_HEADERS/jsscripting_global.h \
    $$PROJECT_HEADERS/JsScriptingComponent.h \

SOURCES += \
    $$PROJECT_SOURCES/JsScriptingComponent.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/JsScripting.definition \

