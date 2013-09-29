PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/jsscriptingui
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/jsscriptingui

HEADERS += \
    $$PROJECT_HEADERS/CodeHighlighter.h \
    $$PROJECT_HEADERS/ColorTheme.h \
    $$PROJECT_HEADERS/jsscriptingui_global.h \
    $$PROJECT_HEADERS/JsScriptingUIComponent.h \
    $$PROJECT_HEADERS/JsScriptingUIInteractiveExtension.h \
    $$PROJECT_HEADERS/LexemeAppearance.h \
    $$PROJECT_HEADERS/ScriptCollectionDialog.h \
    $$PROJECT_HEADERS/ScriptCollectionModel.h \
    $$PROJECT_HEADERS/ScriptConsoleView.h \
    $$PROJECT_HEADERS/ScriptUnitView.h \
    $$PROJECT_HEADERS/ShowScriptsOperation.h \

SOURCES += \
    $$PROJECT_SOURCES/CodeHighlighter.cpp \
    $$PROJECT_SOURCES/ColorTheme.cpp \
    $$PROJECT_SOURCES/JsScriptingUIComponent.cpp \
    $$PROJECT_SOURCES/JsScriptingUIInteractiveExtension.cpp \
    $$PROJECT_SOURCES/LexemeAppearance.cpp \
    $$PROJECT_SOURCES/ScriptCollectionDialog.cpp \
    $$PROJECT_SOURCES/ScriptCollectionModel.cpp \
    $$PROJECT_SOURCES/ScriptConsoleView.cpp \
    $$PROJECT_SOURCES/ScriptUnitView.cpp \
    $$PROJECT_SOURCES/ShowScriptsOperation.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.JsScriptingUI.definition \

FORMS += \
    $$PROJECT_SOURCES/ScriptCollectionDialog.ui \
    $$PROJECT_SOURCES/ScriptConsoleView.ui \
    $$PROJECT_SOURCES/ScriptUnitView.ui \

RESOURCES += \
    $$PROJECT_SOURCES/jsscriptingui.qrc \

