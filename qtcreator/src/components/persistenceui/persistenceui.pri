PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/persistenceui
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/persistenceui

HEADERS += \
    $$PROJECT_HEADERS/LoadOperation.h \
    $$PROJECT_HEADERS/persistenceUI_api.h \
    $$PROJECT_HEADERS/PersistenceUIComponent.h \
    $$PROJECT_HEADERS/PersistenceUIInteractiveExtension.h \
    $$PROJECT_HEADERS/SaveOperation.h \

SOURCES += \
    $$PROJECT_SOURCES/LoadOperation.cpp \
    $$PROJECT_SOURCES/PersistenceUIComponent.cpp \
    $$PROJECT_SOURCES/PersistenceUIInteractiveExtension.cpp \
    $$PROJECT_SOURCES/SaveOperation.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.PersistenceUI.definition \

RESOURCES += \
    $$PROJECT_SOURCES/persistenceui.qrc \

