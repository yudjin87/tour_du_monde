PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/componentsystemui
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/componentsystemui

HEADERS += \
    $$PROJECT_HEADERS/ComponentDefinitionsModel.h \
    $$PROJECT_HEADERS/ComponentManagementInteractiveExtension.h \
    $$PROJECT_HEADERS/ComponentsDialog.h \
    $$PROJECT_HEADERS/componentsystem_ui_global.h \
    $$PROJECT_HEADERS/ComponentSystemUIComponent.h \
    $$PROJECT_HEADERS/InstallComponentsOperation.h \
    $$PROJECT_HEADERS/ShowComponentsOperation.h \

SOURCES += \
    $$PROJECT_SOURCES/ComponentDefinitionsModel.cpp \
    $$PROJECT_SOURCES/ComponentManagementInteractiveExtension.cpp \
    $$PROJECT_SOURCES/ComponentsDialog.cpp \
    $$PROJECT_SOURCES/ComponentSystemUIComponent.cpp \
    $$PROJECT_SOURCES/InstallComponentsOperation.cpp \
    $$PROJECT_SOURCES/ShowComponentsOperation.cpp \

FORMS += \
    $$PROJECT_SOURCES/ComponentsDialog.ui \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.ComponentSystemUI.definition \

RESOURCES += \
    $$PROJECT_SOURCES/componentsystemui.qrc \

