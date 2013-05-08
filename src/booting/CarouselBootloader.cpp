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
void CarouselBootloader::configureComponentManager()
{
    m_logger->log("Initializing component manager", ILogger::Debug, ILogger::Low);
    m_logger->log(QString("Adding %1 components to the component manager").arg(m_componentProvider->components().count()), ILogger::Debug, ILogger::Low);

    foreach(IComponent *component, m_componentProvider->components()) {
        m_componentManager->addComponent(component);
        m_logger->log(QString("%1 component has been added to the component manager").arg(component->name()), ILogger::Debug, ILogger::Low);
    }
}

//------------------------------------------------------------------------------
void CarouselBootloader::configureServiceLocator()
{
    // TODO:
    // give a chanse to avoid default registration
    m_serviceLocator->registerInstance<IComponentProvider>(m_componentProvider);
    m_serviceLocator->registerInstance<ILogger>(m_logger);
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
    m_logger = createLogger();
    m_logger->log("Logger has been created", ILogger::Debug, ILogger::Low);

    m_logger->log("Creating IComponentManager", ILogger::Debug, ILogger::Low);
    m_componentManager = createComponentManager();

    m_logger->log("Creating IComponentProvider", ILogger::Debug, ILogger::Low);
    m_componentProvider = createComponentProvider();

    m_logger->log("Creating IServiceLocator", ILogger::Debug, ILogger::Low);
    m_serviceLocator = createServiceLocator();

    m_logger->log("Creating Main Window", ILogger::Debug, ILogger::Low);
    m_mainWindow = createMainWindow();

    m_logger->log("Configuring IComponentProvider", ILogger::Debug, ILogger::Low);
    configureComponentProvider();

    m_logger->log("Configuring IServiceLocator", ILogger::Debug, ILogger::Low);
    configureServiceLocator();

    m_logger->log("Initializing IComponentProvider", ILogger::Debug, ILogger::Low);
    initialiseComponentProvider();

    m_logger->log("Configuring IComponentManager", ILogger::Debug, ILogger::Low);
    configureComponentManager();

    m_logger->log("Loading sequence completed", ILogger::Debug, ILogger::Low);
}

//------------------------------------------------------------------------------
