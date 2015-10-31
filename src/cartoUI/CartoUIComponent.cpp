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

#include "cartoUI/CartoUIComponent.h"
#include "cartoUI/CartoUIInteractiveExtension.h"
#include "cartoUI/MapView.h"

#include <display/IDisplay.h>

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>
#include <components/interactivity/IInteractionService.h>
#include <components/interactivity/InputDispatcher.h>

#include <QtWidgets/QMainWindow>

static const QByteArray productName("CartoUI");

CartoUIComponent::CartoUIComponent(QObject *parent /*= nullptr*/)
    : BaseComponent("org.carousel.demos.CartoUI", parent)
{
    IInteractiveExtension *interactiveExtension = new CartoUIInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("org.carousel.demos.Geodatabase", 1, 0);
    addParent("org.carousel.demos.Display", 1, 0);
    addParent("org.carousel.demos.DisplayWidgets", 1, 0);
    addParent("org.carousel.demos.Carto", 1, 0);
    setShortName("Carto UI");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

CartoUIComponent::~CartoUIComponent()
{
}

bool CartoUIComponent::onStartup(IServiceLocator *serviceLocator)
{
    //------ Map view
    QMainWindow *mainWindow = serviceLocator->locate<QMainWindow>();
    IDisplay *display = serviceLocator->locate<IDisplay>();
    MapView* mapView = new MapView(*display, mainWindow);
    mainWindow->setCentralWidget(mapView);

    // -------------
    IInteractionService* interactionService = serviceLocator->locate<IInteractionService>();
    interactionService->setDispatcher(new InputDispatcher());
    interactionService->dispatcher()->setSender(mapView);
    interactionService->dispatcher()->activate();

    return true;
}

void CartoUIComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IInteractionService* interactionService = serviceLocator->locate<IInteractionService>();
    interactionService->setDispatcher(nullptr);

    QMainWindow *mainWindow = serviceLocator->locate<QMainWindow>();
    QWidget* centralWidget = mainWindow->centralWidget();
    if (MapView* mapView = dynamic_cast<MapView*>(centralWidget))
    {
        mainWindow->setCentralWidget(nullptr);
        delete mapView;
    }
}

EXPORT_COMPONENT(CartoUIComponent)


