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

#include "EnableComponentCommand.h"

#include <componentsystem/IComponent.h>
#include <componentsystem/IComponentManager.h>

//------------------------------------------------------------------------------
EnableComponentCommand::EnableComponentCommand(IComponentManager *manager, QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_manager(manager)
{
}

//------------------------------------------------------------------------------
EnableComponentCommand::~EnableComponentCommand()
{
}

//------------------------------------------------------------------------------
void EnableComponentCommand::addComponentToDisable(IComponent *component)
{
    m_componentsToDisable.insert(component);
}

//------------------------------------------------------------------------------
void EnableComponentCommand::addComponentToEnable(IComponent *component)
{
    m_componentsToEnable.insert(component);
}

//------------------------------------------------------------------------------
void EnableComponentCommand::addComponentToSwitchState(IComponent *component)
{
    if (component->availability() == IComponent::Enabled)
        m_componentsToDisable.insert(component);
    else if (component->availability() == IComponent::Disabled)
        m_componentsToEnable.insert(component);
}

//------------------------------------------------------------------------------
QList<IComponent *> EnableComponentCommand::componentsToDisable() const
{
    return m_componentsToDisable.toList();
}

//------------------------------------------------------------------------------
QList<IComponent *> EnableComponentCommand::componentsToEnable() const
{
    return m_componentsToEnable.toList();
}

//------------------------------------------------------------------------------
void EnableComponentCommand::redo()
{
    m_manager->startupComponents(m_componentsToEnable.toList());
    m_manager->shutdownComponents(m_componentsToDisable.toList());
}

//------------------------------------------------------------------------------
void EnableComponentCommand::undo()
{
    m_manager->startupComponents(m_componentsToDisable.toList());
    m_manager->shutdownComponents(m_componentsToEnable.toList());
}

//------------------------------------------------------------------------------
