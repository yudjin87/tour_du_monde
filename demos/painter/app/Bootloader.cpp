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

#include <componentsystem/CompositeComponentProvider.h>
#include <componentsystem/DirectoryComponentProvider.h>
#include <componentsystem/IComponentManager.h>
#include <componentsystem/IComponent.h>
#include <componentsystemui/ComponentSystemUIComponent.h>
#include <interactivity/InteractionServiceComponent.h>
#include <undo/UndoComponent.h>

#include <QtCore/QCoreApplication>

//------------------------------------------------------------------------------
Bootloader::Bootloader()
{
}

//------------------------------------------------------------------------------
void Bootloader::_configureComponentProvider()
{
    CompositeComponentProvider *provider = static_cast<CompositeComponentProvider *>(m_componentProvider);
    provider->addProvider(new DirectoryComponentProvider("./components"));
    provider->addProvider(new DirectoryComponentProvider("./installedComponents"));
    provider->registerComponent(new InteractionServiceComponent());
    provider->registerComponent(new ComponentSystemUIComponent());
    provider->registerComponent(new UndoComponent());
}

//------------------------------------------------------------------------------
IComponentProvider *Bootloader::_createComponentProvider()
{
    return new CompositeComponentProvider();
}

//------------------------------------------------------------------------------
QMainWindow *Bootloader::_createMainWindow()
{
    return new MainWindow();
}

//------------------------------------------------------------------------------
