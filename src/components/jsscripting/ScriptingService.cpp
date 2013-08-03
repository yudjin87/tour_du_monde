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

#include "ScriptingService.h"
#include "ScriptConsole.h"
#include "ScriptManager.h"
#include "ServiceLocatorWrapper.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>
#include <components/interactivity/ICatalogs.h>

#include <QtWidgets/QMainWindow>
#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptingService");
}

//------------------------------------------------------------------------------
ScriptingService::ScriptingService(IServiceLocator *locator, QObject *parent)
    : m_wrapper(nullptr)
    , m_console(nullptr)
    , m_scriptManager(nullptr)
{
    m_scriptManager = new ScriptManager(this, this);
    m_wrapper = new ServiceLocatorWrapper(locator, this);
    m_console = new ScriptConsole(this);
    setUpEngine(m_console->engine(), m_console->output());

    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptingService::~ScriptingService()
{
}

//------------------------------------------------------------------------------
IScriptConsole *ScriptingService::console()
{
    return m_console;
}

//------------------------------------------------------------------------------
ScriptManager *ScriptingService::manager()
{
    return m_scriptManager;
}

//------------------------------------------------------------------------------
QScriptEngine *ScriptingService::createEngine(QString *output, QObject *parent)
{
    Log.d("Creating new script engine.");
    QScriptEngine *engine = new QScriptEngine(parent);
    setUpEngine(engine, output);

    return engine;
}

//------------------------------------------------------------------------------
ServiceLocatorWrapper *ScriptingService::locatorWrapper()
{
    return m_wrapper;
}

//------------------------------------------------------------------------------
const ServiceLocatorWrapper *ScriptingService::locatorWrapper() const
{
    return m_wrapper;
}

//------------------------------------------------------------------------------
void ScriptingService::setLocatorWrapper(ServiceLocatorWrapper *locatorWrapper)
{
    delete m_wrapper;
    m_wrapper = locatorWrapper;

    if (m_wrapper != nullptr)
        m_wrapper->setParent(this);

    setUpEngine(m_console->engine(), nullptr); // TODO: temp
}

// TODO: temp
#include <QtCore/QTextStream>
//------------------------------------------------------------------------------
QScriptValue myPrintFunction(QScriptContext *context, QScriptEngine *engine, void *out)
{
    QString *outP = static_cast<QString *>(out);
    QString result;
    QTextStream stream(&result);
    int i = 0;
    for (; i < context->argumentCount(); ++i) {
        if (i > 0)
            stream << " ";
        stream << context->argument(i).toString();
    }

    if (i > 0)
        stream << '\n';

    if (outP != nullptr)
        outP->append(*stream.string());

    return engine->undefinedValue();
}

//------------------------------------------------------------------------------
void ScriptingService::setUpEngine(QScriptEngine *engine, QString *output)
{
    if (output != nullptr)
        output->clear();

    QScriptValue value = engine->newQObject(m_wrapper);
    engine->globalObject().setProperty("serviceLocator", value);

    QScriptValue fun = engine->newFunction(myPrintFunction, (void *)output);
    engine->globalObject().setProperty("print", fun);
}

//------------------------------------------------------------------------------
