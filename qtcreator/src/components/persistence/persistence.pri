PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/persistence
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/persistence

HEADERS += \
    $$PROJECT_HEADERS/CarouselPersistenceDelegate.h \
    $$PROJECT_HEADERS/IPersistenceDelegate.h \
    $$PROJECT_HEADERS/IPersistenceService.h \
    $$PROJECT_HEADERS/IPersistExtension.h \
    $$PROJECT_HEADERS/persistence_global.h \
    $$PROJECT_HEADERS/PersistenceComponent.h \
    $$PROJECT_HEADERS/PersistenceService.h \

SOURCES += \
    $$PROJECT_SOURCES/CarouselPersistenceDelegate.cpp \
    $$PROJECT_SOURCES/PersistenceComponent.cpp \
    $$PROJECT_SOURCES/PersistenceService.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.Persistence.definition \

