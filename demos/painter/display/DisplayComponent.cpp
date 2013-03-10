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

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <framework/AbstractApplication.h>
#include <interactivity/IInteractionService.h>
#include <interactivity/InputInterceptor.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
DisplayComponent::DisplayComponent(QObject *parent)
    : BaseComponent("Display", parent)
{
    mp_definition->addParent("Interactivity");
}

//------------------------------------------------------------------------------
DisplayComponent::~DisplayComponent()
{
}

//------------------------------------------------------------------------------
bool DisplayComponent::_onStartup(QObject *ip_initData)
{
    AbstractApplication *app = qobject_cast<AbstractApplication *>(ip_initData);
    if (app == nullptr)
        return false;

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene);
    view->scale(50000, 50000);

    QMainWindow *mainWindow = app->serviceLocator().locate<QMainWindow>();
    mainWindow->setCentralWidget(view);

    app->serviceLocator().registerInstance<QGraphicsScene>(scene);

    IInteractionService* interactionService = app->serviceLocator().locate<IInteractionService>();
    interactionService->setInputInterceptor(new InputInterceptor());
    interactionService->inputInterceptor()->setSender(view->viewport());
    interactionService->inputInterceptor()->activate();

    return true;
}

//------------------------------------------------------------------------------
void DisplayComponent::_onShutdown()
{
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(DisplayComponent)

//------------------------------------------------------------------------------
