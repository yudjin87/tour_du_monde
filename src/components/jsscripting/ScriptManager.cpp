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

#include "ScriptManager.h"
#include "ScriptUnit.h"
#include "IScriptEngineFactory.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QDirIterator>
#include <QtCore/QtAlgorithms>
#include <QtCore/QScopedPointer>
#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
typedef QScopedPointer<QScriptEngine> QScriptEnginePtr;

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptManager");
}

//------------------------------------------------------------------------------
ScriptManager::ScriptManager(IScriptEngineFactory *factory, QObject *parent)
    : QObject(parent)
    , m_factory(factory)
    , m_scripts(Scripts())
{

}

//------------------------------------------------------------------------------
ScriptManager::~ScriptManager()
{
    qDeleteAll(m_scripts);
    m_scripts.clear();
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptManager::addScript(const QString &fileName)
{
    auto it = m_scripts.find(fileName);
    if (it != m_scripts.end())
        return *it;

    ScriptUnit *unit = new ScriptUnit(fileName);
    // TODO: handle errors
    unit->load();
    m_scripts.insert(fileName, unit);
    scriptAdded(unit);
    return unit;
}

//------------------------------------------------------------------------------
void ScriptManager::runScript(IScriptUnit *script, QString *output, bool *error)
{
    if (script == nullptr)
        return;

    if (!m_scripts.values().contains(script)) {
        Log.w(QString("Cannot run unknown script \"%1\"").arg(script->absoluteFilePath()));
        return;
    }

    QString scriptCode = script->scriptText();
    if (scriptCode.isEmpty()) {
        Log.w("Empty script - nothing to evaluate");
        return;
    }

    if (!script->fileName().isEmpty())
        script->save();

    QScriptEnginePtr engine(m_factory->createEngine(output));
    QScriptValue result = engine->evaluate(scriptCode);
    if (!result.isError()) {
        if (error != nullptr)
            *error = false;

        return;
    }

    QString scriptError = QString("Script error:\"%1\"").arg(result.toString());
    Log.w(scriptError);

    if (output != nullptr)
        *output = result.toString();

    if (error != nullptr)
        *error = true;
}

//------------------------------------------------------------------------------
void ScriptManager::addScripts(const QString &directory)
{
    static QStringList nameFilters {"*.js"};
    static QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
    static QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;

    QDirIterator iterator(directory, nameFilters, filters, flags);
    while (iterator.hasNext()) {
        QString fileName = iterator.next();
        addScript(fileName);
    }
}

//------------------------------------------------------------------------------
ScriptManager::Scripts ScriptManager::scripts() const
{
    return m_scripts;
}

//------------------------------------------------------------------------------
