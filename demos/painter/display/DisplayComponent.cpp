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

#include "DisplayComponent.h"
#include "SimpleDisplay.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <interactivity/IInteractionService.h>
#include <interactivity/InputInterceptor.h>
#include <utils/IServiceLocator.h>

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>

//------------------------------------------------------------------------------
static const QByteArray productName("Display");

//------------------------------------------------------------------------------
DisplayComponent::DisplayComponent(QObject *parent)
    : BaseComponent("Display", parent)
{
    addParent("Interactivity");
    addParent("Geometry");
    setProductName(productName);
    setProvider("Carousel");
}

//------------------------------------------------------------------------------
DisplayComponent::~DisplayComponent()
{
}

//------------------------------------------------------------------------------
void DisplayComponent::onShutdown(IServiceLocator *serviceLocator)
{
//    QGraphicsScene *scene = serviceLocator->unregisterInstance<QGraphicsScene>();
//    QGraphicsView *view = scene->views().first();

//    delete scene;
//    delete view;

    IInteractionService* interactionService = serviceLocator->locate<IInteractionService>();
    interactionService->setInputInterceptor(nullptr);
}

//------------------------------------------------------------------------------
bool DisplayComponent::onStartup(IServiceLocator *serviceLocator)
{
//    QGraphicsScene *scene = new QGraphicsScene();
//    QGraphicsView *view = new QGraphicsView(scene);
//    view->scale(50000, 50000);

    QMainWindow *mainWindow = serviceLocator->locate<QMainWindow>();
    //mainWindow->setCentralWidget(view);

    SimpleDisplay *display = new SimpleDisplay(mainWindow);
    mainWindow->setCentralWidget(display);
    serviceLocator->registerInstance<IDisplay>(display);

    IInteractionService* interactionService = serviceLocator->locate<IInteractionService>();
    interactionService->setInputInterceptor(new InputInterceptor());
    //interactionService->inputInterceptor()->setSender(view->viewport());
    interactionService->inputInterceptor()->setSender(display);
    interactionService->inputInterceptor()->activate();

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(DisplayComponent)

//------------------------------------------------------------------------------
