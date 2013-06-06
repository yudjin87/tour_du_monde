/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */
#ifndef IBOOTLOADER_H
#define IBOOTLOADER_H

#include "booting/booting_global.h"

#include <QtCore/QObject>

class IServiceLocator;

/*!
 * @brief
 *   The abstract IBootloader class provides a basic bootstrapping sequence and hooks
 *   that specific implementations can override.
 * @details
 *   The bootloader instance is one of the first instances who starts Carousel mechanism.
 *   Mainly, is starts a @a registration @a phase.
 *
 *   It creates and registers an IServiceLocator itself and common services, like LoggerFacade,
 *   IComponentManager and, optionally, QMainWindow for the GUI applications. QMainWindow is
 *   just a shell or frame for the application, it is absolutely empty, but then new components
 *   could populate it with menus, toolbars, dock widgets and the central widget.
 *
 *   Usually an IBootloader is implemented (in BootloaderBase or in more specific CarouselBootloader
 *   class) as a sequence of pairs @a create<smth>() - @a configure<smth>() methods, and each of them
 *   could be overridden to replace default instantiation or default configuration.
 *   For example, to use your own logger system it is just needed to override BootloaderBase::createLoggerEngine()
 *   method.
 *
 *   After bootloading process the configured IServiceLocator is available through
 *   serviceLocator() method. Later it will be injected to the all components and other
 *   elements during @a configuration @a phase, when they will start or initialize. It is needed to register/locate to
 *   common services and your components' services.
 *
 *   To start new application you also should to override BootloaderBase::createComponentProvider() or
 *   BootloaderBase::configureComponentProvider() method to determine way in which your application will
 *   be populated by the components. For example, here is a component @a provider which will load components
 *   from the @a "./components" directory at the @a start-time and which also has four built-in components,
 *   configured statically at the @a compile-time:
 * @code
 *   IComponentProvider *MyBootloader::createComponentProvider()
 *   {
 *       CompositeComponentProvider *provider = new CompositeComponentProvider();
 *       provider->addProvider(new DirectoryComponentProvider("./components"));
 *       provider->registerComponent(new InteractionServiceComponent());
 *       provider->registerComponent(new ComponentSystemUIComponent());
 *       provider->registerComponent(new UndoComponent());
 *       return provider;
 *   }
 * @endcode
 *
 *   Then just pass bootloader to the application:
 * @code
 *   #include "MyBootloader.h"
 *   #include <framework/AbstractApplication.h>
 *
 *   int main(int argc, char *argv[])
 *   {
 *       AbstractApplication application(argc, argv);
 *
 *       MyBootloader bootloader;
 *       return application.runApplicationLoop(bootloader);
 *   }
 * @endcode
 */
class BOOTING_API IBootloader : public QObject
{
    Q_OBJECT
public:
    IBootloader(){}
    virtual ~IBootloader(){}

    /*!
     * @details
     *   Runs the bootloading process.
     */
    virtual void run() = 0;

    /*!
     * @details
     *   Gets the service locator, which should contains base objects after
     *   bootloading.
     *
     * @note You can use service locator instance only after running bootloading
     *   sequence.
     * @sa run
     */
    virtual IServiceLocator *serviceLocator() const = 0;

private:
    Q_DISABLE_COPY(IBootloader)
};

#endif // IBOOTLOADER_H
