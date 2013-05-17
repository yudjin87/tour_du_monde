\mainpage Carousel documentation

Carousel
========

Carousel is a managed component library for desktop applications that helps to extending core functionality of the application by external or internal components. An extension (component) can provide a toolbar with new tools, menus,  commands or dock widgets, listen for and respond to events, perform feature validation, and so on. 

There are Carousel's basic concepts: **Components**, **Providers**, **Installers**, **Bootloaders** and **Service Locator**.

Components
----------

An IComponent is a base unit of the Carousel, that can contain UI and/or logic features, provides or exposes some services for the other components. The instances of the IComponent class could
be registered statically in code or discovered by other ways - e.g., loaded from the specified paths at start-time or by demand.

Components are integrated in the application by the **Providers**. Different providers specify different component configuring and loading time - the simplest **ComponentProvider** means **compile-time** components populating:

	IComponentProvider *Bootloader::createComponentProvider()
	{
		IComponentProvider *provider = new ComponentProvider();
		provider->registerComponent(new InteractionServiceComponent());
		provider->registerComponent(new DisplayComponent());

		return provider;
	}

DirectoryComponentProvider can discover and load components	on **run-time**. It uses to load custom components (which may appear as custom installed plugins) from the specified library path. For example, this directory provider will discover and load (if it is possible) all components from the **./components** directory at the **startup-time**:

	IComponentProvider *Bootloader::createComponentProvider()
	{
		DirectoryComponentProvider *directoryProvider = new DirectoryComponentProvider("./components");

		return directoryProvider;
	}	

You also can use FileComponentProvider to load component by demand (e.g., user wants to load just-downloaded component) on **run-time**.

External components can be loaded in right order (if they have a dependencies) from the defining paths or can be configured statically in the code (internal components).

Providers
---------

Installers
----------

Bootloaders
-----------

Service Locator
---------------

Build
=====
Read the BUILD.txt to generate MSVC/Xcode solutions using cmake.

Supported compilers (tested ones):
==================================
<ol>
<li>msvc-10</li>
<li>msvc-11</li>
<li>mingw</li>
<li>gcc-4.4.5</li>
</ol>
