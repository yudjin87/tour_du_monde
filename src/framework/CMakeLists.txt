###############################################################################
# framework project
set(CRSL_PROJECT_NAME "Framework")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/AbstractApplication.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/AbstractApplication.h 
    ${CRSL_TARGET_HEADERS}/framework_global.h 
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
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTGUI_LIBRARY})
