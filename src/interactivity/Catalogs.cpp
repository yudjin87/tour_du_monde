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

#include "Catalogs.h"

#include "CommandCatalog.h"
#include "DockWidgetCatalog.h"
#include "MenuCatalog.h"
#include "ToolBarCatalog.h"

#include <QtGui/QMainWindow>

#include <assert.h>

//------------------------------------------------------------------------------
Catalogs::Catalogs(QMainWindow &i_shell, QObject *ip_startUpData)
    : mp_commandCatalog(new CommandCatalog())
    , mp_dockWidgetCatalog(new DockWidgetCatalog(i_shell))
    , mp_menuCatalog(nullptr)
    , mp_toolBarCatalog(new ToolBarCatalog(i_shell))
{
    assert(i_shell.menuBar() != nullptr);

    mp_menuCatalog = new MenuCatalog(*i_shell.menuBar());
    mp_commandCatalog->setStartupData(ip_startUpData);
}

//------------------------------------------------------------------------------
Catalogs::~Catalogs()
{
    delete mp_commandCatalog;
    mp_commandCatalog = nullptr;
    delete mp_dockWidgetCatalog;
    mp_dockWidgetCatalog = nullptr;
    delete mp_menuCatalog;
    mp_menuCatalog = nullptr;
    delete mp_toolBarCatalog;
    mp_toolBarCatalog = nullptr;
}

//------------------------------------------------------------------------------
ICommandCatalog &Catalogs::commandCatalog()
{
    return const_cast<ICommandCatalog &>(static_cast<const Catalogs &>(*this).commandCatalog());
}

//------------------------------------------------------------------------------
const ICommandCatalog &Catalogs::commandCatalog() const
{
    return *mp_commandCatalog;
}

//------------------------------------------------------------------------------
IDockWidgetCatalog &Catalogs::dockWidgetCatalog()
{
    return const_cast<IDockWidgetCatalog &>(static_cast<const Catalogs &>(*this).dockWidgetCatalog());
}

//------------------------------------------------------------------------------
const IDockWidgetCatalog &Catalogs::dockWidgetCatalog() const
{
    return *mp_dockWidgetCatalog;
}

//------------------------------------------------------------------------------
IMenuCatalog &Catalogs::menuCatalog()
{
    return const_cast<IMenuCatalog &>(static_cast<const Catalogs &>(*this).menuCatalog());
}

//------------------------------------------------------------------------------
const IMenuCatalog &Catalogs::menuCatalog() const
{
    return *mp_menuCatalog;
}

//------------------------------------------------------------------------------
IToolBarCatalog &Catalogs::toolBarCatalog()
{
    return const_cast<IToolBarCatalog &>(static_cast<const Catalogs &>(*this).toolBarCatalog());
}

//------------------------------------------------------------------------------
const IToolBarCatalog &Catalogs::toolBarCatalog() const
{
    return *mp_toolBarCatalog;
}

//------------------------------------------------------------------------------
