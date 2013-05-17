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

#include <componentsystem/ComponentExport.h>
#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
JsScriptingComponent::JsScriptingComponent(QObject *parent)
    : BaseComponent("JsScripting", parent)
{
    setProductName("JsScripting");
    setDescription(description);
    setProvider("Carousel");
    addParent("Interactivity");
}

//------------------------------------------------------------------------------
JsScriptingComponent::~JsScriptingComponent()
{
    if (started())
        qWarning("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void JsScriptingComponent::onShutdown()
{
}

//------------------------------------------------------------------------------
bool JsScriptingComponent::onStartup(QObject *initData)
{
    if (initData == nullptr)
        return false;

    AbstractApplication *app = dynamic_cast<AbstractApplication *>(initData);
    if (app == nullptr)
        return false;

    IServiceLocator &locator = app->serviceLocator();
    Q_UNUSED(locator)

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(JsScriptingComponent)

//------------------------------------------------------------------------------
