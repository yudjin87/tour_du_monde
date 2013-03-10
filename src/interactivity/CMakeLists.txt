cmake_minimum_required(VERSION 2.8)

###############################################################################
# interactivity project
set(CRSL_PROJECT_NAME "Interactivity")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/CarouselComponentConfigurationDelegate.cpp 
    ${CRSL_TARGET_SOURCES}/CarouselInteractionService.cpp 
    ${CRSL_TARGET_SOURCES}/Catalogs.cpp 
    ${CRSL_TARGET_SOURCES}/Command.cpp 
    ${CRSL_TARGET_SOURCES}/CommandCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/ConfigurationChanges.cpp 
    ${CRSL_TARGET_SOURCES}/DialogService.cpp 
    ${CRSL_TARGET_SOURCES}/DockWidgetCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/InputInterceptor.cpp 
    ${CRSL_TARGET_SOURCES}/InteractionServiceComponent.cpp 
    ${CRSL_TARGET_SOURCES}/MenuCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/ToolBarCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/ToolBase.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/CarouselComponentConfigurationDelegate.h 
    ${CRSL_TARGET_HEADERS}/CarouselInteractionService.h 
    ${CRSL_TARGET_HEADERS}/Catalogs.h 
    ${CRSL_TARGET_HEADERS}/Command.h 
    ${CRSL_TARGET_HEADERS}/CommandCatalog.h 
    ${CRSL_TARGET_HEADERS}/ConfigurationChanges.h 
    ${CRSL_TARGET_HEADERS}/DialogService.h 
    ${CRSL_TARGET_HEADERS}/DockWidgetCatalog.h 
    ${CRSL_TARGET_HEADERS}/ICatalogs.h 
    ${CRSL_TARGET_HEADERS}/ICommand.h 
    ${CRSL_TARGET_HEADERS}/ICommandCatalog.h 
    ${CRSL_TARGET_HEADERS}/IComponentConfigurationDelegate.h 
    ${CRSL_TARGET_HEADERS}/IDialogService.h 
    ${CRSL_TARGET_HEADERS}/IDockWidgetCatalog.h 
    ${CRSL_TARGET_HEADERS}/IInputInterceptor.h 
    ${CRSL_TARGET_HEADERS}/IInputReceiver.h 
    ${CRSL_TARGET_HEADERS}/IInteractionService.h 
    ${CRSL_TARGET_HEADERS}/IInteractiveExtension.h 
    ${CRSL_TARGET_HEADERS}/IMenuCatalog.h 
    ${CRSL_TARGET_HEADERS}/InputInterceptor.h 
    ${CRSL_TARGET_HEADERS}/InteractionServiceComponent.h 
    ${CRSL_TARGET_HEADERS}/interactivity_global.h 
    ${CRSL_TARGET_HEADERS}/ITool.h 
    ${CRSL_TARGET_HEADERS}/IToolBarCatalog.h 
    ${CRSL_TARGET_HEADERS}/MenuCatalog.h 
    ${CRSL_TARGET_HEADERS}/ToolBarCatalog.h 
    ${CRSL_TARGET_HEADERS}/ToolBase.h 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/Interactivity.definition 
)

######################################################################
# Qt generated files
qt4_wrap_cpp(__HEADERS_MOC ${__HEADERS})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS} ${__OTHER_FILES})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Logging Utils ComponentSystem)

###############################################################################
# Qt dependencies
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTCORE_LIBRARY})
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTGUI_LIBRARY})

###############################################################################
# Copy definition to the output directory, right near the library
set(__RT_DIRECTORY "")
get_target_property(__RT_DIRECTORY ${CRSL_PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" ${__RT_DIRECTORY})
