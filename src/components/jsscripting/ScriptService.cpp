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

#include "ScriptService.h"
#include "ScriptConsole.h"
#include "ServiceLocatorWrapper.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptService");
}

//------------------------------------------------------------------------------
ScriptService::ScriptService(IServiceLocator *locator, QObject *parent)
    : m_wrapper(nullptr)
    , m_console(nullptr)
    , m_engines(QSet<QScriptEngine *>())
{
    m_wrapper = new ServiceLocatorWrapper(locator, this);
    m_console = new ScriptConsole(createEngine(), this);

    setParent(parent);
}

//------------------------------------------------------------------------------
IScriptConsole *ScriptService::console()
{
    return m_console;
}

//------------------------------------------------------------------------------
QScriptEngine *ScriptService::createEngine()
{
    Log.d("Creating new script engine.");
    QScriptEngine *engine = new QScriptEngine();
    m_engines.insert(engine);
    setUpEngine(engine);

    return engine;
}

//------------------------------------------------------------------------------
void ScriptService::deleteEngine(QScriptEngine *engine)
{
    if (!m_engines.remove(engine))
        Log.w("Cannot delete unexisting engine!");
}

//------------------------------------------------------------------------------
ServiceLocatorWrapper *ScriptService::locatorWrapper()
{
    return m_wrapper;
}

//------------------------------------------------------------------------------
const ServiceLocatorWrapper *ScriptService::locatorWrapper() const
{
    return m_wrapper;
}

//------------------------------------------------------------------------------
void ScriptService::setLocatorWrapper(ServiceLocatorWrapper *locatorWrapper)
{
    delete m_wrapper;
    m_wrapper = locatorWrapper;

    if (m_wrapper != nullptr)
        m_wrapper->setParent(this);

    for (QScriptEngine *engine : m_engines)
        setUpEngine(engine);
}

//------------------------------------------------------------------------------
void ScriptService::setUpEngine(QScriptEngine *engine)
{
    QScriptValue value = engine->newQObject(m_wrapper);
    engine->globalObject().setProperty("serviceLocator", value);
}

//------------------------------------------------------------------------------
