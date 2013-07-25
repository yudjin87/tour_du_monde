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
#include "ScriptConsole.h"
#include "ServiceLocatorWrapper.h"

#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtScript/QScriptEngine>
#include <QtWidgets/QMainWindow>

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
    , m_engine(nullptr)
    , m_wrapper(nullptr)
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
    if (started())
        Log.w("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void JsScriptingComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IScriptConsole *console = serviceLocator->unregisterInstance<IScriptConsole>();
    delete console;

    delete m_wrapper;
    m_wrapper = nullptr;

    delete m_engine;
    m_engine = nullptr;
}

//------------------------------------------------------------------------------
bool JsScriptingComponent::onStartup(IServiceLocator *serviceLocator)
{
    m_engine = new QScriptEngine();

    IScriptConsole *console = new ScriptConsole(m_engine);
    serviceLocator->registerInstance<IScriptConsole>(console);

    ServiceLocatorWrapper *wrapper = new ServiceLocatorWrapper(serviceLocator);
    QScriptValue value = m_engine->newQObject(wrapper);
    m_engine->globalObject().setProperty("serviceLocator", value);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(JsScriptingComponent)

//------------------------------------------------------------------------------
