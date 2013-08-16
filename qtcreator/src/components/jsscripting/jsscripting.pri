PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/jsscripting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/jsscripting

HEADERS += \
    $$PROJECT_HEADERS/CarouselScriptEngineConfigurationDelegate.h \
    $$PROJECT_HEADERS/CodeHighlighter.h \
    $$PROJECT_HEADERS/ColorTheme.h \
    $$PROJECT_HEADERS/IScriptCollection.h \
    $$PROJECT_HEADERS/IScriptConsole.h \
    $$PROJECT_HEADERS/IScriptEngineConfigurationDelegate.h \
    $$PROJECT_HEADERS/IScriptEngineFactory.h \
    $$PROJECT_HEADERS/IScriptExtension.h \
    $$PROJECT_HEADERS/IScriptingService.h \
    $$PROJECT_HEADERS/IScriptUnit.h \
    $$PROJECT_HEADERS/jsscripting_global.h \
    $$PROJECT_HEADERS/JsScriptingComponent.h \
    $$PROJECT_HEADERS/JsScriptingInteractiveExtension.h \
    $$PROJECT_HEADERS/LexemeAppearance.h \
    $$PROJECT_HEADERS/prototypes/ComponentDefinitionPrototype.h \
    $$PROJECT_HEADERS/prototypes/PointClass.h \
    $$PROJECT_HEADERS/prototypes/PointFPrototype.h \
    $$PROJECT_HEADERS/prototypes/PointPrototype.h \
    $$PROJECT_HEADERS/prototypes/RectFPrototype.h \
    $$PROJECT_HEADERS/ScriptCollection.h \
    $$PROJECT_HEADERS/ScriptCollectionDialog.h \
    $$PROJECT_HEADERS/ScriptCollectionModel.h \
    $$PROJECT_HEADERS/ScriptConsole.h \
    $$PROJECT_HEADERS/ScriptConsoleView.h \
    $$PROJECT_HEADERS/ScriptingService.h \
    $$PROJECT_HEADERS/ScriptUnit.h \
    $$PROJECT_HEADERS/ScriptUnitView.h \
    $$PROJECT_HEADERS/ServiceLocatorWrapper.h \
    $$PROJECT_HEADERS/ShowScriptsOperation.h \

SOURCES += \
    $$PROJECT_SOURCES/CarouselScriptEngineConfigurationDelegate.cpp \
    $$PROJECT_SOURCES/CodeHighlighter.cpp \
    $$PROJECT_SOURCES/ColorTheme.cpp \
    $$PROJECT_SOURCES/JsScriptingComponent.cpp \
    $$PROJECT_SOURCES/JsScriptingInteractiveExtension.cpp \
    $$PROJECT_SOURCES/LexemeAppearance.cpp \
    $$PROJECT_SOURCES/prototypes/ComponentDefinitionPrototype.cpp \
    $$PROJECT_SOURCES/prototypes/PointClass.cpp \
    $$PROJECT_SOURCES/prototypes/PointFPrototype.cpp \
    $$PROJECT_SOURCES/prototypes/PointPrototype.cpp \
    $$PROJECT_SOURCES/prototypes/RectFPrototype.cpp \
    $$PROJECT_SOURCES/ScriptCollection.cpp \
    $$PROJECT_SOURCES/ScriptCollectionDialog.cpp \
    $$PROJECT_SOURCES/ScriptCollectionModel.cpp \
    $$PROJECT_SOURCES/ScriptConsole.cpp \
    $$PROJECT_SOURCES/ScriptConsoleView.cpp \
    $$PROJECT_SOURCES/ScriptingService.cpp \
    $$PROJECT_SOURCES/ScriptUnit.cpp \
    $$PROJECT_SOURCES/ScriptUnitView.cpp \
    $$PROJECT_SOURCES/ServiceLocatorWrapper.cpp \
    $$PROJECT_SOURCES/ShowScriptsOperation.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.JsScripting.definition \

FORMS += \
    $$PROJECT_SOURCES/ScriptCollectionDialog.ui \
    $$PROJECT_SOURCES/ScriptConsoleView.ui \
    $$PROJECT_SOURCES/ScriptUnitView.ui \

RESOURCES += \
    $$PROJECT_SOURCES/jsscripting.qrc \

