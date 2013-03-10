cmake_minimum_required(VERSION 2.8)

###############################################################################
# booting project
set(CRSL_PROJECT_NAME "Booting")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/BootloaderBase.cpp 
    ${CRSL_TARGET_SOURCES}/CarouselBootloader.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/booting_global.h 
    ${CRSL_TARGET_HEADERS}/BootloaderBase.h 
    ${CRSL_TARGET_HEADERS}/CarouselBootloader.h 
    ${CRSL_TARGET_HEADERS}/IBootloader.h 
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

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Logging Utils ComponentSystem)

###############################################################################
# Qt dependencies
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTCORE_LIBRARY})
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTGUI_LIBRARY})
