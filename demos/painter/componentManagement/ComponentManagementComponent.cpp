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

#include "ComponentManagementComponent.h"
#include "ComponentManagementInteractiveExtension.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <framework/AbstractApplication.h>

//------------------------------------------------------------------------------
ComponentManagementComponent::ComponentManagementComponent(QObject *parent /*= nullptr*/)
    : BaseComponent("ComponentManagement", parent)
{
    IInteractiveExtension *interactiveExtension = new ComponentManagementInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("Interactivity");
}

//------------------------------------------------------------------------------
ComponentManagementComponent::~ComponentManagementComponent()
{
}

//------------------------------------------------------------------------------
bool ComponentManagementComponent::_onStartup(QObject *ip_initData)
{
    AbstractApplication *app = qobject_cast<AbstractApplication *>(ip_initData);
    if (app == nullptr)
        return false;

    return true;
}

//------------------------------------------------------------------------------
void ComponentManagementComponent::_onShutdown()
{
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(ComponentManagementComponent)

//------------------------------------------------------------------------------
