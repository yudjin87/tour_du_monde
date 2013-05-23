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

#include "InteractionServiceComponent.h"

#include "CarouselInteractionService.h"
#include "DialogService.h"

#include <componentsystem/ComponentExport.h>
#include <componentsystem/IComponentManager.h>
#include <logging/LoggerFacade.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("InteractionServiceComponent");
}

//------------------------------------------------------------------------------
class InteractionServiceComponent::InteractionServiceComponentPrivate
{
public:
    InteractionServiceComponentPrivate();
    ~InteractionServiceComponentPrivate();

    void onShutdown(IServiceLocator *serviceLocator);
    bool onStartup(IServiceLocator *serviceLocator);

private:
    CarouselInteractionService *m_service;
    IDialogService *m_dialogService;
};

//------------------------------------------------------------------------------
static const QByteArray description(
        "The Interactivity component is a main component of GUI based\r\n"
        "application. If your components add new operations or menus, or\r\n"
        "dockable widgets - they should be a child to Interactivity\r\n"
        "component. This mean a dependency of component parent name:\r\n"
        "\"Interactivity\".");

//------------------------------------------------------------------------------
InteractionServiceComponent::InteractionServiceComponent(QObject *parent)
    : BaseComponent("Interactivity", parent)
    , d(new InteractionServiceComponentPrivate())
{
    setProductName("Interactivity");
    setDescription(description);
    setProvider("Carousel");
}

//------------------------------------------------------------------------------
InteractionServiceComponent::~InteractionServiceComponent()
{
    delete d;
    d = nullptr;
}

//------------------------------------------------------------------------------
void InteractionServiceComponent::onShutdown(IServiceLocator *serviceLocator)
{
    d->onShutdown(serviceLocator);
}

//------------------------------------------------------------------------------
bool InteractionServiceComponent::onStartup(IServiceLocator *serviceLocator)
{
    return d->onStartup(serviceLocator);
}

//------------------------------------------------------------------------------
InteractionServiceComponent::InteractionServiceComponentPrivate::InteractionServiceComponentPrivate()
    : m_service(nullptr)
    , m_dialogService(nullptr)
{
}

//------------------------------------------------------------------------------
InteractionServiceComponent::InteractionServiceComponentPrivate::~InteractionServiceComponentPrivate()
{
    if (m_service != nullptr || m_dialogService != nullptr )
        Log.w("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void InteractionServiceComponent::InteractionServiceComponentPrivate::onShutdown(IServiceLocator *serviceLocator)
{
    if (m_service == nullptr || m_dialogService == nullptr )
         Log.w("Logic error: onStartup() should be called before onShutdown().");

    IInteractionService *service = serviceLocator->unregisterInstance<IInteractionService>();
    delete service;
    m_service = nullptr;

    IDialogService *dialogService = serviceLocator->unregisterInstance<IDialogService>();
    delete dialogService;
    m_dialogService = nullptr;
}

//------------------------------------------------------------------------------
bool InteractionServiceComponent::InteractionServiceComponentPrivate::onStartup(IServiceLocator *serviceLocator)
{
    if (m_service != nullptr || m_dialogService != nullptr )
         Log.w("Logic error: onShutdown() was not called.");

    // IDialogService registration
    QMainWindow *mainWindow = serviceLocator->locate<QMainWindow>();
    m_dialogService = new DialogService(mainWindow, serviceLocator);
    serviceLocator->registerInstance<IDialogService>(m_dialogService);

    // IInteractionService registration
    m_service = new CarouselInteractionService(serviceLocator, mainWindow, serviceLocator->locate<IComponentManager>());
    serviceLocator->registerInstance<IInteractionService>(m_service);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(InteractionServiceComponent)

//------------------------------------------------------------------------------
