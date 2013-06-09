###############################################################################
# Add concrete projects to the group
add_subdirectory(componentsystemui)
add_subdirectory(interactivity)
add_subdirectory(undo)
add_subdirectory(jsscripting)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(Interactivity Logging Utils ComponentSystem)
add_dependencies(ComponentSystemUI ComponentSystem)
add_dependencies(Undo Interactivity)
add_dependencies(JsScripting Interactivity)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET ComponentSystemUI PROPERTY FOLDER "src/components")
set_property(TARGET Interactivity PROPERTY FOLDER "src/components")
set_property(TARGET Undo PROPERTY FOLDER "src/components")
set_property(TARGET JsScripting PROPERTY FOLDER "src/components")
