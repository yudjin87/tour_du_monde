PROJECT_SOURCES = $$CPP_SOURCE_TREE/componentsystemUI
PROJECT_HEADERS = $$HPP_SOURCE_TREE/componentsystemUI

SOURCES += \
    $$PROJECT_SOURCES/ComponentDefinitionsAdapter.cpp \
    $$PROJECT_SOURCES/ComponentDefinitionsModel.cpp \
    $$PROJECT_SOURCES/ComponentsDialog.cpp

HEADERS += \
    $$PROJECT_HEADERS/ComponentDefinitionsAdapter.h \
    $$PROJECT_HEADERS/ComponentDefinitionsModel.h \
    $$PROJECT_HEADERS/componentsystem_ui_global.h \
    $$PROJECT_HEADERS/ComponentsDialog.h
