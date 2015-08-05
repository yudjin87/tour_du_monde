/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "Bootloader.h"
#include "LoggerEngine.h"

#include <carousel/componentsystem/CompositeComponentProvider.h>
#include <carousel/componentsystem/DirectoryComponentProvider.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/componentsystem/IComponent.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/logging/ILoggerEngineCreator.h>

#include <components/componentsystemui/ComponentSystemUIComponent.h>
#include <components/jsscripting/JsScriptingComponent.h>
#include <components/jsscriptingui/JsScriptingUIComponent.h>
#include <components/interactivity/InteractionServiceComponent.h>
#include <components/undo/UndoComponent.h>
#include <components/persistence/PersistenceComponent.h>
#include <components/persistenceui/PersistenceUIComponent.h>

Bootloader::Bootloader()
    : CarouselBootloader()
{
}

void Bootloader::configureComponentProvider()
{
    CompositeComponentProvider *provider = static_cast<CompositeComponentProvider *>(m_componentProvider);
    //provider->addProvider(new DirectoryComponentProvider("./installedComponents"));
    provider->addProvider(new DirectoryComponentProvider("./externalSource"));
    provider->registerComponent(new ComponentSystemUIComponent());
    provider->registerComponent(new InteractionServiceComponent());
    provider->registerComponent(new JsScriptingComponent());
    provider->registerComponent(new JsScriptingUIComponent());
    provider->registerComponent(new UndoComponent());
    provider->registerComponent(new PersistenceComponent());
    provider->registerComponent(new PersistenceUIComponent());
}

IComponentProvider *Bootloader::createComponentProvider()
{
    return new CompositeComponentProvider();
}

void Bootloader::onLoadingSequenceFinised()
{
    m_mainWindow.show();
}

ILoggerEngineCreator *Bootloader::createLoggerEngine()
{
    return CarouselBootloader::createLoggerEngine();
    //return new LoggerEngineCreator();
}

void Bootloader::onLoadingSequenceStarting()
{
    CarouselBootloader::onLoadingSequenceStarting();
    serviceLocator()->registerInstance<QMainWindow>(&m_mainWindow);
}

