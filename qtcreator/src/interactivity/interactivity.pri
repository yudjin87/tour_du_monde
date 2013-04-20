PROJECT_SOURCES = $$CPP_SOURCE_TREE/interactivity
PROJECT_HEADERS = $$HPP_SOURCE_TREE/interactivity

SOURCES += \
    $$PROJECT_SOURCES/CarouselComponentConfigurationDelegate.cpp \
    $$PROJECT_SOURCES/CarouselInteractionService.cpp \
    $$PROJECT_SOURCES/Catalogs.cpp \
    $$PROJECT_SOURCES/Operation.cpp \
    $$PROJECT_SOURCES/OperationCatalog.cpp \
    $$PROJECT_SOURCES/ConfigurationChanges.cpp \
    $$PROJECT_SOURCES/DialogService.cpp \
    $$PROJECT_SOURCES/DockWidgetCatalog.cpp \
    $$PROJECT_SOURCES/InputInterceptor.cpp \
    $$PROJECT_SOURCES/InteractionServiceComponent.cpp \
    $$PROJECT_SOURCES/MenuCatalog.cpp \
    $$PROJECT_SOURCES/ToolBarCatalog.cpp \
    $$PROJECT_SOURCES/ToolBase.cpp \

HEADERS += \
    $$PROJECT_HEADERS/CarouselComponentConfigurationDelegate.h \
    $$PROJECT_HEADERS/CarouselInteractionService.h \
    $$PROJECT_HEADERS/Catalogs.h \
    $$PROJECT_HEADERS/Operation.h \
    $$PROJECT_HEADERS/OperationCatalog.h \
    $$PROJECT_HEADERS/ConfigurationChanges.h \
    $$PROJECT_HEADERS/DialogService.h \
    $$PROJECT_HEADERS/DockWidgetCatalog.h \
    $$PROJECT_HEADERS/ICatalogs.h \
    $$PROJECT_HEADERS/IOperation.h \
    $$PROJECT_HEADERS/IOperationCatalog.h \
    $$PROJECT_HEADERS/IComponentConfigurationDelegate.h \
    $$PROJECT_HEADERS/IDialogService.h \
    $$PROJECT_HEADERS/IDockWidgetCatalog.h \
    $$PROJECT_HEADERS/IInputInterceptor.h \
    $$PROJECT_HEADERS/IInputReceiver.h \
    $$PROJECT_HEADERS/IInteractionService.h \
    $$PROJECT_HEADERS/IInteractiveExtension.h \
    $$PROJECT_HEADERS/IMenuCatalog.h \
    $$PROJECT_HEADERS/InputInterceptor.h \
    $$PROJECT_HEADERS/InteractionServiceComponent.h \
    $$PROJECT_HEADERS/interactivity_global.h \
    $$PROJECT_HEADERS/ITool.h \
    $$PROJECT_HEADERS/IToolBarCatalog.h \
    $$PROJECT_HEADERS/MenuCatalog.h \
    $$PROJECT_HEADERS/ToolBarCatalog.h \
    $$PROJECT_HEADERS/ToolBase.h \

OTHER_FILES += \
    $$PROJECT_SOURCES/Interactivity.definition \

