PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/persistence
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/persistence

HEADERS += \
    $$PROJECT_HEADERS/persistence_global.h \
    $$PROJECT_HEADERS/PersistenceComponent.h \

SOURCES += \
    $$PROJECT_SOURCES/PersistenceComponent.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.Persistence.definition \

