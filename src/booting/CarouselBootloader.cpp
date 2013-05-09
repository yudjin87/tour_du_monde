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

#include "CarouselBootloader.h"

#include <componentsystem/ComponentManager.h>
#include <componentsystem/IComponent.h>
#include <componentsystem/IComponentProvider.h>
#include <logging/LoggerFacade.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade log = LoggerFacade::createLogger("CarouselBootloader");
}

//------------------------------------------------------------------------------
CarouselBootloader::CarouselBootloader()
{
}

//------------------------------------------------------------------------------
CarouselBootloader::~CarouselBootloader()
{
    LoggerFacade::installLoggerEngine(nullptr);
}

//------------------------------------------------------------------------------
void CarouselBootloader::configureComponentManager()
{
    log.i("Initializing component manager.");
    log.i(QString("Adding %1 components to the component manager.").arg(m_componentProvider->components().count()));

    foreach(IComponent *component, m_componentProvider->components()) {
        m_componentManager->addComponent(component);
        log.i(QString("%1 component has been added to the component manager.").arg(component->name()));
    }
}

//------------------------------------------------------------------------------
void CarouselBootloader::configureServiceLocator()
{
    // TODO:
    // give a chanse to avoid default registration
    m_serviceLocator->registerInstance<IComponentProvider>(m_componentProvider);
    m_serviceLocator->registerInstance<IComponentManager>(m_componentManager);
    m_serviceLocator->registerInstance<QMainWindow>(m_mainWindow);
}

//------------------------------------------------------------------------------
void CarouselBootloader::initialiseComponentProvider()
{
    m_componentProvider->initialize();
}

//------------------------------------------------------------------------------
void CarouselBootloader::safeRun()
{
    m_logger = createLoggerEngine();

    LoggerFacade::installLoggerEngine(m_logger);
    log.i("Logger has been created.");

    log.i("Creating IComponentManager.");
    m_componentManager = createComponentManager();

    log.i("Creating IComponentProvider.");
    m_componentProvider = createComponentProvider();

    log.i("Creating IServiceLocator.");
    m_serviceLocator = createServiceLocator();

    log.i("Creating MainWindow.");
    m_mainWindow = createMainWindow();

    log.i("Configuring IComponentProvider.");
    configureComponentProvider();

    log.i("Configuring IServiceLocator.");
    configureServiceLocator();

    log.i("Initializing IComponentProvider.");
    initialiseComponentProvider();

    log.i("Configuring IComponentManager.");
    configureComponentManager();

    log.i("Loading sequence completed.");
}

//------------------------------------------------------------------------------
