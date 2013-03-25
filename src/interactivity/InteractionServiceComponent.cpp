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
#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMainWindow>
//------------------------------------------------------------------------------
class InteractionServiceComponent::InteractionServiceComponentPrivate
{
public:
    InteractionServiceComponentPrivate();
    ~InteractionServiceComponentPrivate();

    void onShutdown();
    bool onStartup(QObject *ip_initData);

private:
    CarouselInteractionService *mp_service;
    IDialogService *mp_dialogService;
};

//------------------------------------------------------------------------------
static const QByteArray description(
        "The Interactivity component is a main component of GUI based\r\n"
        "application. If your components add new commands or menus, or\r\n"
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
}

//------------------------------------------------------------------------------
InteractionServiceComponent::~InteractionServiceComponent()
{
    delete d;
    d = nullptr;
}

//------------------------------------------------------------------------------
void InteractionServiceComponent::_onShutdown()
{
    d->onShutdown();
}

//------------------------------------------------------------------------------
bool InteractionServiceComponent::_onStartup(QObject *ip_initData)
{
    return d->onStartup(ip_initData);
}

//------------------------------------------------------------------------------
InteractionServiceComponent::InteractionServiceComponentPrivate::InteractionServiceComponentPrivate()
    : mp_service(nullptr)
    , mp_dialogService(nullptr)
{
}

//------------------------------------------------------------------------------
InteractionServiceComponent::InteractionServiceComponentPrivate::~InteractionServiceComponentPrivate()
{
    if (mp_service != nullptr
            || mp_dialogService != nullptr )
        qWarning("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void InteractionServiceComponent::InteractionServiceComponentPrivate::onShutdown()
{
    if (mp_service == nullptr
            || mp_dialogService == nullptr )
        qWarning("Logic error: onStartup() should be called before onShutdown().");

    delete mp_service;
    mp_service = nullptr;
    delete mp_dialogService;
    mp_dialogService = nullptr;
}

//------------------------------------------------------------------------------
bool InteractionServiceComponent::InteractionServiceComponentPrivate::onStartup(QObject *ip_initData)
{
    if (mp_service != nullptr
            || mp_dialogService != nullptr )
        qWarning("Logic error: onShutdown() was not called.");

    if (ip_initData == nullptr)
        return false;

    AbstractApplication *app = dynamic_cast<AbstractApplication *>(ip_initData);
    if (app == nullptr)
        return false;

    mp_service = new CarouselInteractionService(*app);
    app->serviceLocator().registerInstance<IInteractionService>(mp_service);

    QMainWindow *mainWindow = app->serviceLocator().locate<QMainWindow>();
    mp_dialogService = new DialogService(mainWindow);
    app->serviceLocator().registerInstance<IDialogService>(mp_dialogService);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(InteractionServiceComponent)

//------------------------------------------------------------------------------
