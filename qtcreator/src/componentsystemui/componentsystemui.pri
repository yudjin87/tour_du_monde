PROJECT_SOURCES = $$CPP_SOURCE_TREE/componentsystemui
PROJECT_HEADERS = $$HPP_SOURCE_TREE/componentsystemui

HEADERS += \
    $$PROJECT_HEADERS/ComponentDefinitionsAdapter.h \
    $$PROJECT_HEADERS/ComponentDefinitionsModel.h \
    $$PROJECT_HEADERS/ComponentsDialog.h \
    $$PROJECT_HEADERS/componentsystem_ui_global.h \
    $$PROJECT_HEADERS/ComponentSystemUIComponent.h

SOURCES += \
    $$PROJECT_SOURCES/ComponentDefinitionsAdapter.cpp \
    $$PROJECT_SOURCES/ComponentDefinitionsModel.cpp \
    $$PROJECT_SOURCES/ComponentsDialog.cpp \
    $$PROJECT_SOURCES/ComponentSystemUIComponent.cpp

FORMS += \
    $$PROJECT_SOURCES/ComponentsDialog.ui

OTHER_FILES += \
    $$PROJECT_SOURCES/ComponentSystemUI.definition
