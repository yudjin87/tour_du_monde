/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "cartoUI/CartoUIInteractiveExtension.h"
#include "cartoUI/LayerTreeModel.h"
#include "cartoUI/LayerTreeView.h"
#include "cartoUI/AddShapeOperation.h"
#include "cartoUI/MapView.h"
#include "cartoUI/CoordsTracker.h"
#include "cartoUI/DefaultNavigationHandler.h"

#include <carto/ITourDuMondeDocumentController.h>
#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>
#include <display/IDisplay.h>

#include <components/interactivity/IInteractionService.h>
#include <components/interactivity/InputDispatcher.h>
#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IDockWidgetCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/IToolBarCatalog.h>
#include <components/interactivity/ToggleActionWrapper.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QListView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QToolBar>

CartoUIInteractiveExtension::CartoUIInteractiveExtension(QObject *parent)
    : QObject(parent)
    , m_layersTree(nullptr)
    , m_serviceLocator(nullptr)
{
}

void CartoUIInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;

    ITourDuMondeDocumentController* docController = serviceLocator->locate<ITourDuMondeDocumentController>();
    connect(docController, &ITourDuMondeDocumentController::activeDocumentChanged, this, &CartoUIInteractiveExtension::onActiveDocumentChanged);
    ITourDuMondeDocument *doc = docController->document();

    IMenuCatalog &menuCatalog = inCatalogs.menuCatalog();
    IDockWidgetCatalog &catalog = inCatalogs.dockWidgetCatalog();
    m_layersTree = new LayerTreeView(menuCatalog);
    m_layersTree->setLayerTreeModel(new LayerTreeModel(doc->map(), serviceLocator));

    QDockWidget *layersDock = catalog.addDockWidget(m_layersTree, "Layers tree");

    Operation *toogleTree = new ToggleActionWrapper(layersDock->toggleViewAction(), QIcon(":/cartoUI/images/layerTree.png"));
    inCatalogs.operationCatalog().add(toogleTree);

    QMenu *viewMenu = inCatalogs.menuCatalog().addMenu("View");
    viewMenu->addAction(toogleTree);

    //------
    IOperationCatalog &operationCatalog = inCatalogs.operationCatalog();
    Operation *addShape = operationCatalog.add(new AddShapeOperation());

    IToolBarCatalog &toolbarCatalog = inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("Shapes");
    toolBar->addAction(addShape);

    QMenu *toolMenu = menuCatalog.addMenu("Tools");
    toolMenu->addAction(addShape);

    //------ Map view
    QMainWindow *mainWindow = serviceLocator->locate<QMainWindow>();
    IDisplay *display = serviceLocator->locate<IDisplay>();

    CoordsTracker* tracker = new CoordsTracker(display, mainWindow->statusBar(), this);
    Q_UNUSED(tracker)

    ITourDuMondeDocumentController* controller = serviceLocator->locate<ITourDuMondeDocumentController>();
    DefaultNavigationHandler* defaultNavigationHandler = new DefaultNavigationHandler(display, controller, this);
    Q_UNUSED(defaultNavigationHandler)
}

void CartoUIInteractiveExtension::onActiveDocumentChanged(ITourDuMondeDocument *document)
{
    m_layersTree->setLayerTreeModel(new LayerTreeModel(document->map(), m_serviceLocator));
}

