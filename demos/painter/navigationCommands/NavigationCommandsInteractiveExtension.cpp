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

#include "NavigationCommandsInteractiveExtension.h"
#include "PanTool.h"
#include "ZoomAllCommand.h"
#include "ZoomInCommand.h"
#include "ZoomOutCommand.h"

#include <framework/AbstractApplication.h>
#include <interactivity/ICatalogs.h>
#include <interactivity/ICommandCatalog.h>
#include <interactivity/IMenuCatalog.h>
#include <interactivity/IToolBarCatalog.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMenu>
#include <QtGui/QToolBar>

//------------------------------------------------------------------------------
NavigationCommandsInteractiveExtension::NavigationCommandsInteractiveExtension(QObject *parent /*= nullptr*/)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void NavigationCommandsInteractiveExtension::configureGui(ICatalogs &i_inCatalogs, AbstractApplication &i_application)
{
    Q_UNUSED(i_inCatalogs);
    Q_UNUSED(i_application);

    ICommandCatalog &commandCatalog = i_inCatalogs.commandCatalog();
    Command *zoomAll = commandCatalog.add(new ZoomAllCommand());
    Command *zoomIn = commandCatalog.add(new ZoomInCommand());
    Command *zoomOut = commandCatalog.add(new ZoomOutCommand());
    Command *pan = commandCatalog.add(new PanTool());

    IToolBarCatalog &toolbarCatalog = i_inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("Navigation");
    toolBar->addAction(zoomAll);
    toolBar->addAction(zoomIn);
    toolBar->addAction(zoomOut);
    toolBar->addAction(pan);

    IMenuCatalog &menuCatalog = i_inCatalogs.menuCatalog();
    QMenu *tools = menuCatalog.findMenu("Tools");
    QMenu *menu = tools->addMenu("Navigation");
    menu->addAction(zoomAll);
    menu->addAction(zoomIn);
    menu->addAction(zoomOut);
    menu->addAction(pan);
}

//------------------------------------------------------------------------------

