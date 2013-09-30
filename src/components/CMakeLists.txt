###############################################################################
# Add concrete projects to the group
add_subdirectory(componentsystemui)
add_subdirectory(interactivity)
add_subdirectory(undo)
add_subdirectory(jsscripting)
add_subdirectory(jsscriptingui)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(org.carousel.Interactivity     Carousel)
add_dependencies(org.carousel.Undo              org.carousel.Interactivity)
add_dependencies(org.carousel.ComponentSystemUI Carousel org.carousel.Undo)
add_dependencies(org.carousel.JsScripting       Carousel)
add_dependencies(org.carousel.JsScriptingUI     org.carousel.Interactivity org.carousel.JsScripting)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET org.carousel.ComponentSystemUI PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.Interactivity PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.Undo PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.JsScripting PROPERTY FOLDER "src/components")
set_property(TARGET org.carousel.JsScriptingUI PROPERTY FOLDER "src/components")
