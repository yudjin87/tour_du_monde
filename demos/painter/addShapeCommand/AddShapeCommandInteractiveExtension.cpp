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

#include "AddShapeCommandInteractiveExtension.h"
#include "AddShapeCommand.h"

#include <framework/AbstractApplication.h>
#include <interactivity/ICatalogs.h>
#include <interactivity/ICommandCatalog.h>
#include <interactivity/IMenuCatalog.h>
#include <interactivity/IToolBarCatalog.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMenu>
#include <QtGui/QToolBar>

//------------------------------------------------------------------------------
AddShapeCommandInteractiveExtension::AddShapeCommandInteractiveExtension(QObject *parent /*= nullptr*/)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void AddShapeCommandInteractiveExtension::configureGui(ICatalogs &i_inCatalogs, AbstractApplication &i_application)
{
    Q_UNUSED(i_inCatalogs);
    Q_UNUSED(i_application);

    ICommandCatalog &commandCatalog = i_inCatalogs.commandCatalog();
    Command *addShape = commandCatalog.add(new AddShapeCommand());

    IToolBarCatalog &toolbarCatalog = i_inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("Shapes");
    toolBar->addAction(addShape);

    IMenuCatalog &menuCatalog = i_inCatalogs.menuCatalog();
    QMenu *menu = menuCatalog.addMenu("Tools");
    menu->addAction(addShape);
}

//------------------------------------------------------------------------------

