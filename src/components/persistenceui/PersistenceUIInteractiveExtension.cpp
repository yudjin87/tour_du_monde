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

#include "components/persistenceui/PersistenceUIInteractiveExtension.h"
#include "components/persistenceui/SaveOperation.h"
#include "components/persistenceui/LoadOperation.h"
#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IToolBarCatalog.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QListView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QToolBar>

PersistenceUIInteractiveExtension::PersistenceUIInteractiveExtension(QObject *parent)
    : QObject(parent)
{
}

void PersistenceUIInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
    IOperationCatalog &operationCatalog = inCatalogs.operationCatalog();
    Operation *save = operationCatalog.add(new SaveOperation());
    Operation *load = operationCatalog.add(new LoadOperation());

    IToolBarCatalog &toolbarCatalog = inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("File");
    toolBar->addAction(save);
    toolBar->addAction(load);

    IMenuCatalog &menuCatalog = inCatalogs.menuCatalog();
    QMenu *file = menuCatalog.addMenu("File");
    file->addAction(save);
    file->addAction(load);
}

