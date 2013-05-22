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

#include "OperationCatalog.h"
#include "DockWidgetCatalog.h"
#include "MenuCatalog.h"
#include "ToolBarCatalog.h"

#include <QtGui/QMainWindow>

#include <assert.h>

//------------------------------------------------------------------------------
Catalogs::Catalogs(QMainWindow &shell, IServiceLocator *serviceLocator)
    : m_operationCatalog(new OperationCatalog())
    , m_dockWidgetCatalog(new DockWidgetCatalog(shell))
    , m_menuCatalog(nullptr)
    , m_toolBarCatalog(new ToolBarCatalog(shell))
{
    assert(shell.menuBar() != nullptr);

    m_menuCatalog = new MenuCatalog(*shell.menuBar());
    m_operationCatalog->setStartupData(serviceLocator);
}

//------------------------------------------------------------------------------
Catalogs::~Catalogs()
{
    delete m_operationCatalog;
    m_operationCatalog = nullptr;
    delete m_dockWidgetCatalog;
    m_dockWidgetCatalog = nullptr;
    delete m_menuCatalog;
    m_menuCatalog = nullptr;
    delete m_toolBarCatalog;
    m_toolBarCatalog = nullptr;
}

//------------------------------------------------------------------------------
IOperationCatalog &Catalogs::operationCatalog()
{
    return const_cast<IOperationCatalog &>(static_cast<const Catalogs &>(*this).operationCatalog());
}

//------------------------------------------------------------------------------
const IOperationCatalog &Catalogs::operationCatalog() const
{
    return *m_operationCatalog;
}

//------------------------------------------------------------------------------
IDockWidgetCatalog &Catalogs::dockWidgetCatalog()
{
    return const_cast<IDockWidgetCatalog &>(static_cast<const Catalogs &>(*this).dockWidgetCatalog());
}

//------------------------------------------------------------------------------
const IDockWidgetCatalog &Catalogs::dockWidgetCatalog() const
{
    return *m_dockWidgetCatalog;
}

//------------------------------------------------------------------------------
IMenuCatalog &Catalogs::menuCatalog()
{
    return const_cast<IMenuCatalog &>(static_cast<const Catalogs &>(*this).menuCatalog());
}

//------------------------------------------------------------------------------
const IMenuCatalog &Catalogs::menuCatalog() const
{
    return *m_menuCatalog;
}

//------------------------------------------------------------------------------
IToolBarCatalog &Catalogs::toolBarCatalog()
{
    return const_cast<IToolBarCatalog &>(static_cast<const Catalogs &>(*this).toolBarCatalog());
}

//------------------------------------------------------------------------------
const IToolBarCatalog &Catalogs::toolBarCatalog() const
{
    return *m_toolBarCatalog;
}

//------------------------------------------------------------------------------
