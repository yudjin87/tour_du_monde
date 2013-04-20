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

#include "ConfigurationChanges.h"

//------------------------------------------------------------------------------
ConfigurationChanges::ConfigurationChanges()
    : m_insertedOperations()
    , m_addedOperations()
    , m_addedDockWidgets()
    , m_addedMenus()
    , m_addedToolbars()
{
}

//------------------------------------------------------------------------------
ConfigurationChanges::~ConfigurationChanges()
{
    m_addedOperations.clear();
    m_insertedOperations.clear();
    m_addedDockWidgets.clear();
    m_addedMenus.clear();
    m_addedToolbars.clear();
}

//------------------------------------------------------------------------------
void ConfigurationChanges::insertAddedOperation(Operation *ip_operation)
{
    m_addedOperations.push_back(ip_operation);
}

//------------------------------------------------------------------------------
void ConfigurationChanges::insertAddedDockWidget(QDockWidget *ip_dockWidget)
{
    m_addedDockWidgets.push_back(ip_dockWidget);
}

//------------------------------------------------------------------------------
void ConfigurationChanges::insertAddedMenu(QMenu *ip_menu)
{
    m_addedMenus.push_back(ip_menu);
}

//------------------------------------------------------------------------------
void ConfigurationChanges::insertAddedToolbar(QToolBar *ip_toolbar)
{
    m_addedToolbars.push_back(ip_toolbar);
}

//------------------------------------------------------------------------------
void ConfigurationChanges::insertInsertedOperation(Operation *ip_operation)
{
    m_insertedOperations.push_back(ip_operation);
}

//------------------------------------------------------------------------------
void ConfigurationChanges::insertRemovedMenu(QMenu *ip_menu)
{
    m_removedMenus.push_back(ip_menu);
}

//------------------------------------------------------------------------------
const ConfigurationChanges::Operations &ConfigurationChanges::addedOperations() const
{
    return m_addedOperations;
}

//------------------------------------------------------------------------------
const ConfigurationChanges::DockWidgets &ConfigurationChanges::addedDockWidgets() const
{
    return m_addedDockWidgets;
}

//------------------------------------------------------------------------------
const ConfigurationChanges::Menus &ConfigurationChanges::addedMenus() const
{
    return m_addedMenus;
}

//------------------------------------------------------------------------------
const ConfigurationChanges::Menus &ConfigurationChanges::removedMenus() const
{
    return m_removedMenus;
}

//------------------------------------------------------------------------------
const ConfigurationChanges::ToolBars &ConfigurationChanges::addedToolbars() const
{
    return m_addedToolbars;
}

//------------------------------------------------------------------------------
const ConfigurationChanges::Operations &ConfigurationChanges::insertedOperations() const
{
    return m_insertedOperations;
}

//------------------------------------------------------------------------------
