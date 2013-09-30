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

#include <carousel/componentsystem/ComponentManager.h>
#include <carousel/componentsystem/IComponent.h>
#include <carousel/componentsystem/IComponentProvider.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("CarouselBootloader");
}

//------------------------------------------------------------------------------
CarouselBootloader::CarouselBootloader()
    : BootloaderBase()
{
}

//------------------------------------------------------------------------------
CarouselBootloader::~CarouselBootloader()
{
    LoggerFacade::installLoggerEngineCreator(nullptr);
}

//------------------------------------------------------------------------------
void CarouselBootloader::configureComponentManager()
{
    Log.i("Initializing component manager.");
    Log.i(QString("Adding %1 components to the component manager.").arg(m_componentProvider->components().count()));

    for (IComponent *component : m_componentProvider->components()) {
        m_componentManager->addComponent(component);
        Log.i(QString("%1 component has been added to the component manager.").arg(component->name()));
    }
}

//------------------------------------------------------------------------------
void CarouselBootloader::configureServiceLocator()
{
    // TODO: give a chanse to avoid default registration
    m_serviceLocator->registerInstance<IComponentProvider>(m_componentProvider);
    m_serviceLocator->registerInstance<IComponentManager>(m_componentManager);
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

    LoggerFacade::installLoggerEngineCreator(m_logger);
    Log.i("Logger has been created.");

    Log.i("Creating IServiceLocator.");
    m_serviceLocator = createServiceLocator();

    Log.i("Starting loading sequence.");
    onLoadingSequenceStarting();

    Log.i("Creating IComponentManager.");
    m_componentManager = createComponentManager();

    Log.i("Creating IComponentProvider.");
    m_componentProvider = createComponentProvider();

    Log.i("Configuring IComponentProvider.");
    configureComponentProvider();

    Log.i("Configuring IServiceLocator.");
    configureServiceLocator();

    Log.i("Initializing IComponentProvider.");
    initialiseComponentProvider();

    Log.i("Configuring IComponentManager.");
    configureComponentManager();

    Log.i("Starting IComponentManager.");
    startComponentManager();

    Log.i("Loading sequence finished.");
    onLoadingSequenceFinised();
}

//------------------------------------------------------------------------------
