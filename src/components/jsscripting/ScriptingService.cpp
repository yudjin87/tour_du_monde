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
#include "ScriptCollection.h"
#include "IScriptUnit.h"
#include "CarouselScriptEngineConfigurationDelegate.h"

#include <carousel/componentsystem/IComponent.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/utils/ObservableList.h>
#include <components/interactivity/ICatalogs.h>

#include <QtWidgets/QMainWindow>
#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptingService");
}

//------------------------------------------------------------------------------
ScriptingService::ScriptingService(IServiceLocator *locator, IComponentManager *manager, QObject *parent)
    : m_componentManager(manager)
    , m_scriptExtensionConfigurationDelegate(new CarouselScriptEngineConfigurationDelegate(locator, this))
    , m_console(new ScriptConsole(this))
    , m_scripts(new ScriptCollection(this, this))
    , m_startScript()
{
    setParent(parent);
    connect(m_componentManager, &IComponentManager::startedUp, this, &ScriptingService::onComponentManagerStartedUp);
}

//------------------------------------------------------------------------------
ScriptingService::ScriptingService(IServiceLocator *locator, IComponentManager *manager, const QString &startScript, QObject *parent)
    : m_componentManager(manager)
    , m_scriptExtensionConfigurationDelegate(new CarouselScriptEngineConfigurationDelegate(locator, this))
    , m_console(new ScriptConsole(this))
    , m_scripts(new ScriptCollection(this, this))
    , m_startScript(startScript)
{
    setParent(parent);
    connect(m_componentManager, &IComponentManager::startedUp, this, &ScriptingService::onComponentManagerStartedUp);
    connect(m_componentManager, &IComponentManager::startedUp, this, &ScriptingService::runStartScript, Qt::QueuedConnection);
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
IScriptCollection *ScriptingService::scripts()
{
    return m_scripts;
}

//------------------------------------------------------------------------------
QScriptEngine *ScriptingService::createEngine(IOutputHandler *output, QObject *parent)
{
    Log.d("Creating new script engine.");
    QScriptEngine *engine = new QScriptEngine(parent);
    setUpEngine(engine, output);

    return engine;
}

//------------------------------------------------------------------------------
IScriptEngineConfigurationDelegate *ScriptingService::delegate()
{
    return m_scriptExtensionConfigurationDelegate;
}

//------------------------------------------------------------------------------
const IScriptEngineConfigurationDelegate *ScriptingService::delegate() const
{
    return m_scriptExtensionConfigurationDelegate;
}

//------------------------------------------------------------------------------
void ScriptingService::setDelegate(IScriptEngineConfigurationDelegate *delegate)
{
    delete m_scriptExtensionConfigurationDelegate;
    m_scriptExtensionConfigurationDelegate = delegate;

    if (m_scriptExtensionConfigurationDelegate != nullptr)
        m_scriptExtensionConfigurationDelegate->setParent(this);

    setUpEngine(m_console->engine(), m_console);
}

//------------------------------------------------------------------------------
void ScriptingService::onComponentManagerStartedUp()
{
    setUpEngine(m_console->engine(), m_console);

    connect(m_componentManager, &IComponentManager::componentStarted, this, &ScriptingService::onComponentStartedUp);
}

//------------------------------------------------------------------------------
void ScriptingService::onComponentStartedUp(IComponent *component)
{
    if (m_scriptExtensionConfigurationDelegate == nullptr)
        return;

    m_scriptExtensionConfigurationDelegate->configureFromComponent(component, m_console->engine());
}

//------------------------------------------------------------------------------
void ScriptingService::setUpEngine(QScriptEngine *engine, IOutputHandler *output)
{
    if (m_scriptExtensionConfigurationDelegate == nullptr) {
        // TODO: clear console engine, uncomment test
        return;
    }

    m_scriptExtensionConfigurationDelegate->configureDefaults(engine, output);

    for (IComponent *comp : m_componentManager->components()) {
        m_scriptExtensionConfigurationDelegate->configureFromComponent(comp, engine);
    }
}

//------------------------------------------------------------------------------
void ScriptingService::runStartScript()
{
    if (m_startScript.isEmpty())
        return;

    IScriptUnit *startScript = m_scripts->createFromFile(m_startScript);
    if (startScript != nullptr) {
        Log.d(QString("Running start script \"%1\" ...").arg(m_startScript));
        startScript->run();
    } else {
        Log.w(QString("Failed to load start script \"%1\"").arg(m_startScript));
    }
}

//------------------------------------------------------------------------------
