###############################################################################
# logging project
set(CRSL_PROJECT_NAME "Logging")
set(CRSL_TARGET_TYPE "carousel")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/LoggerFacade.cpp 
    ${CRSL_TARGET_SOURCES}/NullLogger.cpp 
    ${CRSL_TARGET_SOURCES}/TextLogger.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/ILoggerEngine.h 
    ${CRSL_TARGET_HEADERS}/ILoggerEngineCreator.h 
    ${CRSL_TARGET_HEADERS}/LoggerFacade.h 
    ${CRSL_TARGET_HEADERS}/logging_global.h 
    ${CRSL_TARGET_HEADERS}/NullLogger.h 
    ${CRSL_TARGET_HEADERS}/TextLogger.h 
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
