###############################################################################
# utils project
set(CRSL_PROJECT_NAME "org.carousel.Persistence")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/CarouselPersistenceDelegate.cpp 
    ${CRSL_TARGET_SOURCES}/PersistenceComponent.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/CarouselPersistenceDelegate.h 
    ${CRSL_TARGET_HEADERS}/IPersistenceDelegate.h 
    ${CRSL_TARGET_HEADERS}/IPersistenceService.h 
    ${CRSL_TARGET_HEADERS}/IPersistExtension.h 
    ${CRSL_TARGET_HEADERS}/persistence_global.h 
    ${CRSL_TARGET_HEADERS}/PersistenceComponent.h 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.Persistence.definition 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Carousel)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
