###############################################################################
# utils project
set(CRSL_PROJECT_NAME "Utils")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/FileUtils.cpp 
    ${CRSL_TARGET_SOURCES}/ServiceLocator.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/Changes.h 
    ${CRSL_TARGET_HEADERS}/FileUtils.h 
    ${CRSL_TARGET_HEADERS}/IListObserver.h 
    ${CRSL_TARGET_HEADERS}/IServiceLocator.h 
    ${CRSL_TARGET_HEADERS}/ListDictionary.h 
    ${CRSL_TARGET_HEADERS}/ObservableList.h 
    ${CRSL_TARGET_HEADERS}/ServiceLocator.h 
    ${CRSL_TARGET_HEADERS}/TypeObjectsMap.h 
    ${CRSL_TARGET_HEADERS}/utils_global.h 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core)
