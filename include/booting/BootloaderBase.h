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
#ifndef BOOTLOADERBASE_H
#define BOOTLOADERBASE_H

#include "booting/booting_global.h"
#include "booting/IBootloader.h"

class IServiceLocator;
class IComponentManager;
class ILogger;
class IComponentProvider;
class QMainWindow;

/*!
 * @brief
 *   The abstract BootloaderBase class provides a basic bootstrapping sequence and hooks
 *   that specific implementations can override.
 * @details
 *   This class must be overriden to provide application specific boot loading sequence.
 *   It is just a template of the carousel's booting steps, so it contains
 *   empty realizations of all @a configure<> methods and instantiates default objects
 *   for the all @a create<> methods. You can derived from this class if you want determine
 *   your own bootloading sequence, but it is recomended to derived from the CarouselBootloader
 *   class and override @a create<> and @a configure<> methods and keep bootloading sequence.
 *
 *   After bootloading process the configured IServiceLocator is available through
 *   serviceLocator() method. You can access IServiceLocator reference using AbstractApplication
 *   and register/locate to the common services and your components' services.
 */
class BOOTING_API BootloaderBase : public IBootloader
{
    Q_OBJECT
public:
    BootloaderBase();
    ~BootloaderBase();

    /*!
     * @details
     *   Runs the bootloading process.
     */
    void run();

    /*!
     * @details
     *   Gets the service locator, which should contains base objects after
     *   bootloading.
     */
    IServiceLocator *serviceLocator() const;

protected:
    /*!
     * @details
     *   Does nothing by default. When overriden in derived classes should add all
     *   components registered in provider to the component manager.
     */
    virtual void _configureComponentManager();

    /*!
     * @details
     *   Does nothing by default. You should override this method in the
     *   your specified bootloader to register new components, or setup
     *   components' discovering path (if you use DirectoryComponentProvider).
     */
    virtual void _configureComponentProvider();

    /*!
     * @details
     *   When overriden in derived classes setups the needed services
     *   such as ILogger, IComponentManager and other.
     */
    virtual void _configureServiceLocator() = 0;

    /*!
     * @details
     *   Creates default component manager using IComponentManager class
     *   and takes ownership.
     */
    virtual IComponentManager *_createComponentManager();

    /*!
     * @details
     *   Creates default provider using ComponentProvider class
     *   and takes ownership.
     */
    virtual IComponentProvider *_createComponentProvider();

    /*!
     * @details
     *   Creates default logger using TextLogger class with @a stdout output
     *   and takes ownership of this logger. Should be overriden in the derived
     *   classes to instantiate your own logger facade over the better logging
     *   system (e.g. log4cplus).
     */
    virtual ILogger *_createLogger();

    /*!
     * @details
     *   Creates default service locator using ServiceLocator class
     *   and takes ownership.
     */
    virtual IServiceLocator *_createServiceLocator();

    /*!
     * @details
     *   Creates default main window class and takes ownership.
     */
    virtual QMainWindow *_createMainWindow();

    /*!
     * @details
     *   Does nothing by default. When overriden in derived classes should call
     *   IComponentProvider::initialize() method for the created component provider.
     */
    virtual void _initialiseComponentProvider();

    /*!
     * @details
     *   It is a safe part of the public run() method, that guaranted it would be called
     *   in derived class only once per instance.
     */
    virtual void _run() = 0;

protected:
    /*!
     * @details
     *   Component manager for the application.
     */
    IComponentManager *m_componentManager;

    /*!
     * @details
     *   Component provider for the application.
     */
    IComponentProvider *m_componentProvider;

    /*!
     * @details
     *   Logger facade used by the bootloader.
     */
    ILogger *m_logger;

    /*!
     * @details
     *   Service locator for the application.
     */
    IServiceLocator *m_serviceLocator;

    /*!
     * @details
     *   Main window (shell) for the application.
     */
    QMainWindow *m_mainWindow;

private:
    bool m_alreadyRunned;
};

#endif // BOOTLOADERBASE_H
