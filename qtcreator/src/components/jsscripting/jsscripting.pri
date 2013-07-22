PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/jsscripting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/jsscripting

HEADERS += \
    $$PROJECT_HEADERS/jsscripting_global.h \
    $$PROJECT_HEADERS/JsScriptingComponent.h \
    $$PROJECT_HEADERS/JsScriptingInteractiveExtension.h \
    $$PROJECT_HEADERS/ScriptConsole.h \

SOURCES += \
    $$PROJECT_SOURCES/JsScriptingComponent.cpp \
    $$PROJECT_SOURCES/JsScriptingInteractiveExtension.cpp \
    $$PROJECT_SOURCES/ScriptConsole.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.JsScripting.definition \

FORMS += \
    $$PROJECT_SOURCES/ScriptConsole.ui \

RESOURCES += \
    $$PROJECT_SOURCES/jsscripting.qrc \

