PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/jsscripting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/jsscripting

HEADERS += \
    $$PROJECT_HEADERS/CodeHighlighter.h \
    $$PROJECT_HEADERS/ColorTheme.h \
    $$PROJECT_HEADERS/IScriptConsole.h \
    $$PROJECT_HEADERS/IScriptEngineFactory.h \
    $$PROJECT_HEADERS/IScriptingService.h \
    $$PROJECT_HEADERS/jsscripting_global.h \
    $$PROJECT_HEADERS/JsScriptingComponent.h \
    $$PROJECT_HEADERS/JsScriptingInteractiveExtension.h \
    $$PROJECT_HEADERS/LexemeAppearance.h \
    $$PROJECT_HEADERS/ScriptConsole.h \
    $$PROJECT_HEADERS/ScriptConsoleView.h \
    $$PROJECT_HEADERS/ScriptingService.h \
    $$PROJECT_HEADERS/ScriptManager.h \
    $$PROJECT_HEADERS/ScriptManagerDialog.h \
    $$PROJECT_HEADERS/ScriptManagerModel.h \
    $$PROJECT_HEADERS/ScriptUnit.h \
    $$PROJECT_HEADERS/ScriptUnitView.h \
    $$PROJECT_HEADERS/ServiceLocatorWrapper.h \
    $$PROJECT_HEADERS/ShowScriptManagerOperation.h \

SOURCES += \
    $$PROJECT_SOURCES/CodeHighlighter.cpp \
    $$PROJECT_SOURCES/ColorTheme.cpp \
    $$PROJECT_SOURCES/JsScriptingComponent.cpp \
    $$PROJECT_SOURCES/JsScriptingInteractiveExtension.cpp \
    $$PROJECT_SOURCES/LexemeAppearance.cpp \
    $$PROJECT_SOURCES/ScriptConsole.cpp \
    $$PROJECT_SOURCES/ScriptConsoleView.cpp \
    $$PROJECT_SOURCES/ScriptingService.cpp \
    $$PROJECT_SOURCES/ScriptManager.cpp \
    $$PROJECT_SOURCES/ScriptManagerDialog.cpp \
    $$PROJECT_SOURCES/ScriptManagerModel.cpp \
    $$PROJECT_SOURCES/ScriptUnit.cpp \
    $$PROJECT_SOURCES/ScriptUnitView.cpp \
    $$PROJECT_SOURCES/ServiceLocatorWrapper.cpp \
    $$PROJECT_SOURCES/ShowScriptManagerOperation.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.JsScripting.definition \

FORMS += \
    $$PROJECT_SOURCES/ScriptConsoleView.ui \
    $$PROJECT_SOURCES/ScriptManagerDialog.ui \
    $$PROJECT_SOURCES/ScriptUnitView.ui \

RESOURCES += \
    $$PROJECT_SOURCES/jsscripting.qrc \

