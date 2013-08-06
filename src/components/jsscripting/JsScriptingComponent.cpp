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

#include "JsScriptingComponent.h"
#include "JsScriptingInteractiveExtension.h"
#include "ScriptingService.h"
#include "ScriptManagerDialog.h"
#include "ScriptManagerModel.h"

#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <components/interactivity/IDialogService.h>
#include <components/interactivity/IInteractionService.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("JsScriptingComponent");
}

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
JsScriptingComponent::JsScriptingComponent(QObject *parent)
    : BaseComponent("org.carousel.JsScripting", parent)
{
    IInteractiveExtension *interactiveExtension = new JsScriptingInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    setShortName("JsScripting");
    setProductName("JsScripting");
    setDescription(description);
    setProvider("Carousel");
    setVersion(1, 0);
    addParent("org.carousel.Interactivity", 1, 0);
}

//------------------------------------------------------------------------------
JsScriptingComponent::~JsScriptingComponent()
{
}

//------------------------------------------------------------------------------
void JsScriptingComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IScriptingService *service = serviceLocator->unregisterInstance<IScriptingService>();
    delete service;
}

//------------------------------------------------------------------------------
bool JsScriptingComponent::onStartup(IServiceLocator *serviceLocator)
{
    IComponentManager *manager = serviceLocator->locate<IComponentManager>();
    IScriptingService *service = new ScriptingService(serviceLocator, manager);
    serviceLocator->registerInstance<IScriptingService>(service);

    // Services
    IDialogService *dialogService = serviceLocator->locate<IDialogService>();
    dialogService->registerDialog<ScriptManagerDialog, ScriptManagerModel>();

    auto scriptManagerModelCreator = [service](){return new ScriptManagerModel(service->manager());};
    serviceLocator->registerType<ScriptManagerModel>(scriptManagerModelCreator);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(JsScriptingComponent)

//------------------------------------------------------------------------------
