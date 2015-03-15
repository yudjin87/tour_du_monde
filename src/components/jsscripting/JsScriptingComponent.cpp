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
#include "ScriptingService.h"

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <algorithm>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("JsScriptingComponent");
}

static const QByteArray description(
        "");

JsScriptingComponent::JsScriptingComponent(QObject *parent)
    : BaseComponent("org.carousel.JsScripting", parent)
{
    setShortName("JsScripting");
    setProductName("JsScripting");
    setDescription(description);
    setProvider("Carousel");
    setVersion(1, 0);
}

JsScriptingComponent::~JsScriptingComponent()
{
}

void JsScriptingComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IScriptingService *service = serviceLocator->unregisterInstance<IScriptingService>();
    delete service;
}

bool JsScriptingComponent::onStartup(IServiceLocator *serviceLocator)
{
    IComponentManager *manager = serviceLocator->locate<IComponentManager>();
    IScriptingService *service = new ScriptingService(serviceLocator, manager, getStartedScriptFromAgrs());
    serviceLocator->registerInstance<IScriptingService>(service);

    return true;
}

QString JsScriptingComponent::getStartedScriptFromAgrs() const
{
    // TODO: Handle optional argument ... may be it should be one more extension
    QStringList args = definition()->arguments();
    auto it = std::find(args.cbegin(), args.cend(), "--start-script");
    if (it == args.cend())
        return QString();

    ++it;
    if (it == args.cend()) {
        Log.e("Wrong parameters. Usage [--start-script <scriptFilePath>]");
        return QString();
    }

    return *it;
}

EXPORT_COMPONENT(JsScriptingComponent)

