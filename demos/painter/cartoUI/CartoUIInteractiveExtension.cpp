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

#include "CartoUIInteractiveExtension.h"
#include "LayersTreeModel.h"

#include <dom/IPainterDocument.h>
#include <dom/IPainterDocumentController.h>
#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IDockWidgetCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/ToggleActionWrapper.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QListView>

//------------------------------------------------------------------------------
CartoUIInteractiveExtension::CartoUIInteractiveExtension(QObject *parent /*= nullptr*/)
{
    setParent(parent);
}

//------------------------------------------------------------------------------
void CartoUIInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    IPainterDocumentController* docController = serviceLocator->locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();

    IDockWidgetCatalog &catalog = inCatalogs.dockWidgetCatalog();
    QListView *view = new QListView();
    view->setModel(new LayersTreeModel(doc->map(), view));
    QDockWidget *layersDock = catalog.addDockWidget(view, "Layers tree");

    Operation *toogleTree = new ToggleActionWrapper(layersDock->toggleViewAction(), QIcon(":/cartoUI/images/layerTree.png"));
    inCatalogs.operationCatalog().add(toogleTree);

    QMenu *viewMenu = inCatalogs.menuCatalog().addMenu("View");
    viewMenu->addAction(toogleTree);
}

//------------------------------------------------------------------------------
