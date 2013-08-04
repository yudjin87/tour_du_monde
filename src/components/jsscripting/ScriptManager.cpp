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

#include <QtCore/QCoreApplication>
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
    : IScriptManager()
    , m_factory(factory)
    , m_scripts(Scripts())
{
    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptManager::~ScriptManager()
{
    qDeleteAll(m_scripts);
    m_scripts.clear();
}

//------------------------------------------------------------------------------
IScriptManager::Scripts ScriptManager::scripts() const
{
    return m_scripts;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptManager::scriptByFileName(const QString &fileName)
{
    QDir dir(QCoreApplication::applicationDirPath());
    QString absoluteName = dir.absoluteFilePath(fileName);

    for (IScriptUnit *script : m_scripts)
        if (script->absoluteFilePath() == absoluteName)
            return script;

    return nullptr;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptManager::createScript()
{
    IScriptUnit *unit = createNewScript();
    m_scripts.push_back(unit);
    emit scriptAdded(unit);
    return unit;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptManager::addScript(const QString &fileName)
{
    IScriptUnit *existedScript = scriptByFileName(fileName);
    if (existedScript != nullptr)
        return existedScript;

    IScriptUnit *unit = createNewScript(&fileName);

    if (!unit->load())
        return nullptr;

    m_scripts.push_back(unit);
    emit scriptAdded(unit);
    return unit;
}

//------------------------------------------------------------------------------
void ScriptManager::removeScript(IScriptUnit *script)
{
    if (!m_scripts.contains(script))
        return;

    m_scripts.removeOne(script);
    emit scriptRemoved(script);
    script->deleteLater();
}

//------------------------------------------------------------------------------
IScriptManager::Scripts ScriptManager::addScripts(const QString &directory)
{
    static QStringList nameFilters {"*.js"};
    static QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
    static QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;

    // Working directory might be different from the app dir (e.g. is tests are run from CMake)
    QDir dir(QCoreApplication::applicationDirPath());
    if (!dir.cd(directory))
        return Scripts();

    QString absoluteDirectory = dir.absolutePath();
    Scripts result;
    QDirIterator iterator(absoluteDirectory, nameFilters, filters, flags);
    while (iterator.hasNext()) {
        QString fileName = iterator.next();
        IScriptUnit *unit = addScript(fileName);
        if (unit != nullptr)
            result.append(unit);
    }

    return result;
}

//------------------------------------------------------------------------------
void ScriptManager::runScript(IScriptUnit *script, QString *output, bool *error)
{
    if (script == nullptr)
        return;

    if (!m_scripts.contains(script)) {
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
IScriptUnit *ScriptManager::createNewScript(const QString *fileName)
{
    return (fileName == nullptr) ? new ScriptUnit() : new ScriptUnit(*fileName);
}

//------------------------------------------------------------------------------
