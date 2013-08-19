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

#include "ScriptCollection.h"
#include "ScriptUnit.h"
#include "IScriptEngineFactory.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDirIterator>
#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptCollection");
}

//------------------------------------------------------------------------------
ScriptCollection::ScriptCollection(IScriptEngineFactory *factory, QObject *parent)
    : IScriptCollection()
    , m_factory(factory)
    , m_scripts(Scripts())
{
    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptCollection::~ScriptCollection()
{
    qDeleteAll(m_scripts);
    m_scripts.clear();
}

//------------------------------------------------------------------------------
IScriptCollection::Scripts ScriptCollection::scripts() const
{
    return m_scripts;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptCollection::scriptByFileName(const QString &fileName)
{
    QDir dir(QCoreApplication::applicationDirPath());
    QString absoluteName = dir.absoluteFilePath(fileName);

    for (IScriptUnit *script : m_scripts)
        if (script->absoluteFilePath() == absoluteName)
            return script;

    return nullptr;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptCollection::create()
{
    IScriptUnit *unit = createNewScript();
    m_scripts.push_back(unit);
    emit scriptAdded(unit);
    return unit;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptCollection::createFromFile(const QString &fileName)
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
void ScriptCollection::remove(IScriptUnit *script)
{
    if (!m_scripts.contains(script))
        return;

    m_scripts.removeOne(script);
    emit scriptRemoved(script);
    script->deleteLater();
}

//------------------------------------------------------------------------------
IScriptCollection::Scripts ScriptCollection::createFromDirectory(const QString &directory)
{
#ifdef Q_COMPILER_INITIALIZER_LISTS // MSVC does not support it yet
    static QStringList nameFilters {"*.js"};
#else
    static QStringList nameFilters("*.js");
#endif // #ifdef Q_COMPILER_INITIALIZER_LISTS

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
        IScriptUnit *unit = createFromFile(fileName);
        if (unit != nullptr)
            result.append(unit);
    }

    return result;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptCollection::createNewScript(const QString *fileName)
{
    return (fileName == nullptr) ? new ScriptUnit(m_factory) : new ScriptUnit(*fileName, m_factory);
}

//------------------------------------------------------------------------------
