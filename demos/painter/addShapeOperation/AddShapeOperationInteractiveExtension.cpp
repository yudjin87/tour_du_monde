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

#include "AddShapeOperationInteractiveExtension.h"
#include "AddShapeOperation.h"

#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IToolBarCatalog.h>

#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

//------------------------------------------------------------------------------
AddShapeOperationInteractiveExtension::AddShapeOperationInteractiveExtension(QObject *parent /*= nullptr*/)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void AddShapeOperationInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator);

    IOperationCatalog &operationCatalog = inCatalogs.operationCatalog();
    Operation *addShape = operationCatalog.add(new AddShapeOperation());

    IToolBarCatalog &toolbarCatalog = inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("Shapes");
    toolBar->addAction(addShape);

    IMenuCatalog &menuCatalog = inCatalogs.menuCatalog();
    QMenu *menu = menuCatalog.addMenu("Tools");
    menu->addAction(addShape);
}

//------------------------------------------------------------------------------

