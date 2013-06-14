###############################################################################
# Add concrete projects to the group
add_subdirectory(componentsystemui)
add_subdirectory(interactivity)
add_subdirectory(undo)
add_subdirectory(jsscripting)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(org.carousel.Interactivity     Logging Utils ComponentSystem)
add_dependencies(org.carousel.ComponentSystemUI ComponentSystem)
add_dependencies(org.carousel.Undo              org.carousel.Interactivity)
add_dependencies(org.carousel.JsScripting       org.carousel.Interactivity)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET org.carousel.ComponentSystemUI PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.Interactivity PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.Undo PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.JsScripting PROPERTY FOLDER "src/components")
