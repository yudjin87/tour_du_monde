PROJECT_SOURCES = $$CPP_SOURCE_TREE/undo
PROJECT_HEADERS = $$HPP_SOURCE_TREE/undo

HEADERS += \
    $$PROJECT_HEADERS/undo_global.h \
    $$PROJECT_HEADERS/UndoComponent.h \
    $$PROJECT_HEADERS/UndoInteractiveExtension.h \
    $$PROJECT_HEADERS/RedoOperation.h \
    $$PROJECT_HEADERS/UndoOperation.h

SOURCES += \
    $$PROJECT_SOURCES/UndoComponent.cpp \
    $$PROJECT_SOURCES/UndoInteractiveExtension.cpp \
    $$PROJECT_SOURCES/RedoOperation.cpp \
    $$PROJECT_SOURCES/UndoOperation.cpp

FORMS += \

OTHER_FILES += \
    $$PROJECT_SOURCES/Undo.definition \

RESOURCES += \
    $$PROJECT_SOURCES/undo.qrc

