###############################################################################
# logging project
set(CRSL_PROJECT_NAME "Logging")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/NullLogger.cpp 
    ${CRSL_TARGET_SOURCES}/TextLogger.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/ILogger.h 
    ${CRSL_TARGET_HEADERS}/logging_global.h 
    ${CRSL_TARGET_HEADERS}/NullLogger.h 
    ${CRSL_TARGET_HEADERS}/TextLogger.h 
)

######################################################################
# Qt generated files
qt4_wrap_cpp(__HEADERS_MOC ${__HEADERS})

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
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTCORE_LIBRARY})
