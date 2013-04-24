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

#include <utils/IServiceLocator.h>
#include <componentsystem/ComponentManager.h>
#include <componentsystem/IComponent.h>
#include <componentsystem/IComponentProvider.h>
#include <logging/ILogger.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
CarouselBootloader::CarouselBootloader()
{
}

//------------------------------------------------------------------------------
CarouselBootloader::~CarouselBootloader()
{
}

//------------------------------------------------------------------------------
void CarouselBootloader::_configureComponentManager()
{
    mp_logger->log("Initializing component manager", ILogger::Debug, ILogger::Low);
    mp_logger->log(QString("Adding %1 components to the component manager").arg(mp_componentProvider->components().count()), ILogger::Debug, ILogger::Low);

    foreach(IComponent *p_component, mp_componentProvider->components()) {
        mp_componentManager->addComponent(p_component);
        mp_logger->log(QString("%1 component has been added to the component manager").arg(p_component->name()), ILogger::Debug, ILogger::Low);
    }
}

//------------------------------------------------------------------------------
void CarouselBootloader::_configureServiceLocator()
{
    // TODO:
    // give a chanse to avoid default registration
    mp_serviceLocator->registerInstance<IComponentProvider>(mp_componentProvider);
    mp_serviceLocator->registerInstance<ILogger>(mp_logger);
    mp_serviceLocator->registerInstance<IComponentManager>(mp_componentManager);
    mp_serviceLocator->registerInstance<QMainWindow>(mp_mainWindow);
}

//------------------------------------------------------------------------------
void CarouselBootloader::_initialiseComponentProvider()
{
    mp_componentProvider->initialize();
}

//------------------------------------------------------------------------------
void CarouselBootloader::_run()
{
    mp_logger = _createLogger();
    mp_logger->log("Logger has been created", ILogger::Debug, ILogger::Low);

    mp_logger->log("Creating IComponentManager", ILogger::Debug, ILogger::Low);
    mp_componentManager = _createComponentManager();

    mp_logger->log("Creating IComponentProvider", ILogger::Debug, ILogger::Low);
    mp_componentProvider = _createComponentProvider();

    mp_logger->log("Creating IServiceLocator", ILogger::Debug, ILogger::Low);
    mp_serviceLocator = _createServiceLocator();

    mp_logger->log("Creating Main Window", ILogger::Debug, ILogger::Low);
    mp_mainWindow = _createMainWindow();

    mp_logger->log("Configuring IComponentProvider", ILogger::Debug, ILogger::Low);
    _configureComponentProvider();

    mp_logger->log("Configuring IServiceLocator", ILogger::Debug, ILogger::Low);
    _configureServiceLocator();

    mp_logger->log("Initializing IComponentProvider", ILogger::Debug, ILogger::Low);
    _initialiseComponentProvider();

    mp_logger->log("Configuring IComponentManager", ILogger::Debug, ILogger::Low);
    _configureComponentManager();

    mp_logger->log("Loading sequence completed", ILogger::Debug, ILogger::Low);
}

//------------------------------------------------------------------------------
