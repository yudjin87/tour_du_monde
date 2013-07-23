PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/jsscripting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/jsscripting

HEADERS += \
    $$PROJECT_HEADERS/IScriptConsole.h \
    $$PROJECT_HEADERS/IScriptService.h \
    $$PROJECT_HEADERS/jsscripting_global.h \
    $$PROJECT_HEADERS/JsScriptingComponent.h \
    $$PROJECT_HEADERS/JsScriptingInteractiveExtension.h \
    $$PROJECT_HEADERS/ScriptConsole.h \
    $$PROJECT_HEADERS/ScriptConsoleView.h \
    $$PROJECT_HEADERS/ScriptService.h \
    $$PROJECT_HEADERS/ServiceLocatorWrapper.h \

SOURCES += \
    $$PROJECT_SOURCES/JsScriptingComponent.cpp \
    $$PROJECT_SOURCES/JsScriptingInteractiveExtension.cpp \
    $$PROJECT_SOURCES/ScriptConsole.cpp \
    $$PROJECT_SOURCES/ScriptConsoleView.cpp \
    $$PROJECT_SOURCES/ScriptService.cpp \
    $$PROJECT_SOURCES/ServiceLocatorWrapper.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.JsScripting.definition \

FORMS += \
    $$PROJECT_SOURCES/ScriptConsoleView.ui \

RESOURCES += \
    $$PROJECT_SOURCES/jsscripting.qrc \

