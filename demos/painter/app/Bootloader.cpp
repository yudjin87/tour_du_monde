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

#include "Bootloader.h"
#include "MainWindow.h"

#include <componentManagement/ComponentManagementComponent.h>
#include <carousel/componentsystem/CompositeComponentProvider.h>
#include <carousel/componentsystem/DirectoryComponentProvider.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/componentsystem/IComponent.h>
#include <components/componentsystemui/ComponentSystemUIComponent.h>
#include <components/jsscripting/JsScriptingComponent.h>
#include <components/interactivity/InteractionServiceComponent.h>
#include <components/undo/UndoComponent.h>

#include <QtCore/QCoreApplication>

//------------------------------------------------------------------------------
Bootloader::Bootloader()
{
}

//------------------------------------------------------------------------------
void Bootloader::configureComponentProvider()
{
    CompositeComponentProvider *provider = static_cast<CompositeComponentProvider *>(m_componentProvider);
    provider->addProvider(new DirectoryComponentProvider("./installedComponents"));
    provider->registerComponent(new ComponentManagementComponent());
    provider->registerComponent(new ComponentSystemUIComponent());
    provider->registerComponent(new InteractionServiceComponent());
    provider->registerComponent(new JsScriptingComponent());
    provider->registerComponent(new UndoComponent());
}

//------------------------------------------------------------------------------
IComponentProvider *Bootloader::createComponentProvider()
{
    return new CompositeComponentProvider();
}

//------------------------------------------------------------------------------
QMainWindow *Bootloader::createMainWindow()
{
    return new MainWindow();
}

//------------------------------------------------------------------------------
