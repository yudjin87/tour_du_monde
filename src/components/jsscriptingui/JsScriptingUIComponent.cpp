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

#include "JsScriptingUIComponent.h"
#include "JsScriptingUIInteractiveExtension.h"
#include "ScriptCollectionDialog.h"
#include "ScriptCollectionModel.h"

#include <components/jsscripting/IScriptConsole.h>
#include <components/jsscripting/IScriptingService.h>
#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <components/interactivity/IDialogService.h>
#include <components/interactivity/IInteractionService.h>

#include <algorithm>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("JsScriptingUIComponent");
}

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
JsScriptingUIComponent::JsScriptingUIComponent(QObject *parent)
    : BaseComponent("org.carousel.JsScriptingUI", parent)
{
    IInteractiveExtension *interactiveExtension = new JsScriptingUIInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    setShortName("JsScriptingUI");
    setProductName("JsScriptingUI");
    setDescription(description);
    setProvider("Carousel");
    setVersion(1, 0);
    addParent("org.carousel.JsScripting", 1, 0);
    addParent("org.carousel.Interactivity", 1, 0);
}

//------------------------------------------------------------------------------
JsScriptingUIComponent::~JsScriptingUIComponent()
{
}

//------------------------------------------------------------------------------
void JsScriptingUIComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
    // TODO: unregister dialog
}

//------------------------------------------------------------------------------
bool JsScriptingUIComponent::onStartup(IServiceLocator *serviceLocator)
{
    IScriptingService *service = serviceLocator->locate<IScriptingService>();

    // Services
    IDialogService *dialogService = serviceLocator->locate<IDialogService>();
    dialogService->registerDialog<ScriptCollectionDialog, ScriptCollectionModel>();

    auto scriptManagerModelCreator = [service](){return new ScriptCollectionModel(service->scripts());};
    serviceLocator->registerType<ScriptCollectionModel>(scriptManagerModelCreator);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(JsScriptingUIComponent)

//------------------------------------------------------------------------------
