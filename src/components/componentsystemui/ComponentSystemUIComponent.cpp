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

#include "ComponentSystemUIComponent.h"
#include "ComponentDefinitionsModel.h"
#include "ComponentsDialog.h"

#include "EnableComponentCommand.h"
#include "InstallComponentsCommand.h"

#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/componentsystem/ComponentDependencies.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <components/interactivity/IDialogService.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentSystemUIComponent");
}

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
ComponentSystemUIComponent::ComponentSystemUIComponent(QObject *parent)
    : BaseComponent("org.carousel.ComponentSystemUI", parent)
{
    setShortName("Component System UI");
    setProductName("ComponentSystemUI");
    setDescription(description);
    setProvider("Carousel");
    addParent("org.carousel.Interactivity");
}

//------------------------------------------------------------------------------
ComponentSystemUIComponent::~ComponentSystemUIComponent()
{
    if (started())
        Log.w("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void ComponentSystemUIComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
    // TODO:
    // Unregister dialogs!
}

//------------------------------------------------------------------------------
bool ComponentSystemUIComponent::onStartup(IServiceLocator *serviceLocator)
{
    IComponentManager *manager = serviceLocator->locate<IComponentManager>();

    // Commands
    auto enableCreator = [manager](){return new EnableComponentCommand(manager);};
    serviceLocator->registerType<EnableComponentCommand>(enableCreator);

    auto installCreator = [manager](){return new InstallComponentsCommand(manager);};
    serviceLocator->registerType<InstallComponentsCommand>(installCreator);

    // Services
    IDialogService *dialogService = serviceLocator->locate<IDialogService>();
    dialogService->registerDialog<ComponentsDialog, ComponentDefinitionsModel>();

    auto componentDefinitionsModelCreator = [manager](){return new ComponentDefinitionsModel(manager->dependencies().components());};
    serviceLocator->registerType<ComponentDefinitionsModel>(componentDefinitionsModelCreator);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(ComponentSystemUIComponent)

//------------------------------------------------------------------------------

