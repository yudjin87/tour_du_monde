###############################################################################
# When included this module adds pathes to boost headers and binaries.
# This module does not intend to export public variables to the parent
# scope.

set(__BOOST_SRC_DIR ${CRSL_THIRD_PARTY_SRC_DIR}/boost)

# Add the boost directory to those the compiler uses to search for include files.
include_directories(${__BOOST_SRC_DIR})

###############################################################################
# Due to MSVC configurations we need to setup both pathes for the boost 
# binaries - release and debug. We can not use CMAKE_BUILD_TYPE value
# because different configurations are possible (e.g. debug_static), so we
# have to setup link directory by hands.
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
  link_directories(${__BOOST_SRC_DIR}/${CRSL_TARGET_OS}${CRSL_TARGET_PLATFORM_BITS}/debug/lib/)
  link_directories(${__BOOST_SRC_DIR}/${CRSL_TARGET_OS}${CRSL_TARGET_PLATFORM_BITS}/release/lib/)
else()
  # For other generators 
  if (CMAKE_BUILD_TYPE MATCHES "debug")
    link_directories(${__BOOST_SRC_DIR}/${CRSL_TARGET_OS}${CRSL_TARGET_PLATFORM_BITS}/debug/lib/)
  else()
    link_directories(${__BOOST_SRC_DIR}/${CRSL_TARGET_OS}${CRSL_TARGET_PLATFORM_BITS}/release/lib/)
  endif()	  
endif()



