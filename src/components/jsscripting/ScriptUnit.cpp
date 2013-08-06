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

#include "ScriptUnit.h"
#include "IScriptEngineFactory.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtGui/QTextDocument>
#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptUnit");
}

//------------------------------------------------------------------------------
ScriptUnit::ScriptUnit(IScriptEngineFactory *factory, QObject *parent)
    : IScriptUnit()
    , m_isLoaded(false)
    , m_fileName("")
    , m_factory(factory)
    , m_script(new QTextDocument(this))
    , m_engine(nullptr)
{
    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptUnit::ScriptUnit(const QString &filePath, IScriptEngineFactory *factory, QObject *parent)
    : IScriptUnit()
    , m_isLoaded(false)
    , m_fileName(absolutePath(filePath))
    , m_factory(factory)
    , m_script(new QTextDocument(this))
    , m_engine(nullptr)
{
    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptUnit::~ScriptUnit()
{
}

//------------------------------------------------------------------------------
bool ScriptUnit::isLoaded() const
{
    return m_isLoaded;
}

//------------------------------------------------------------------------------
QString ScriptUnit::fileName() const
{
    QFileInfo file(m_fileName);
    return file.fileName();
}

//------------------------------------------------------------------------------
QString ScriptUnit::scriptText() const
{
    return m_script->toPlainText();
}

//------------------------------------------------------------------------------
QString ScriptUnit::absoluteFilePath() const
{
    return m_fileName;
}

//------------------------------------------------------------------------------
QTextDocument *ScriptUnit::script()
{
    return m_script;
}

//------------------------------------------------------------------------------
const QTextDocument *ScriptUnit::script() const
{
    return m_script;
}

//------------------------------------------------------------------------------
bool ScriptUnit::load()
{
    if (m_isLoaded)
        return true;

    if (m_fileName.isEmpty()) {
        Log.w("No file name specified");
        return false;
    }

    QFile scriptFile(m_fileName);
    if (!scriptFile.open(QIODevice::ReadOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(m_fileName);
        Log.w(error);
        return false;
    }

    m_script->setPlainText(scriptFile.readAll());

    m_isLoaded = true;
    m_script->setModified(false);
    return m_isLoaded;
}

//------------------------------------------------------------------------------
bool ScriptUnit::load(const QString &filePath)
{
    m_fileName = absolutePath(filePath);
    return load();
}

//------------------------------------------------------------------------------
void ScriptUnit::clear()
{
    m_script->clear();
}

//------------------------------------------------------------------------------
bool ScriptUnit::save()
{
    return saveAs(m_fileName);
}

//------------------------------------------------------------------------------
bool ScriptUnit::saveAs(const QString &fileName)
{
    if (!m_script->isModified())
        return true;

    if (!saveToFile(fileName))
        return false;

    m_fileName = fileName;
    m_script->setModified(false);
    return true;
}

//------------------------------------------------------------------------------
bool ScriptUnit::run(QString *output)
{
    const QString &script = scriptText();
    if (script.isEmpty()) {
        Log.w("Empty script - nothing to evaluate");
        return false;
    }

    if (!fileName().isEmpty())
        save();

    // Do not destroy previous engine, because script may still executes
    m_engine.reset(m_factory->createEngine(output));
    QScriptValue result = m_engine->evaluate(script);
    if (!result.isError())
        return true;

    QString scriptError = QString("Script error:\"%1\"").arg(result.toString());
    Log.w(scriptError);

    if (output != nullptr)
        *output = result.toString();

    return false;
}

//------------------------------------------------------------------------------
QString ScriptUnit::absolutePath(const QString &filePath)
{
    QDir dir(QCoreApplication::applicationDirPath());
    return dir.absoluteFilePath(filePath);
}

//------------------------------------------------------------------------------
bool ScriptUnit::saveToFile(const QString &filePath)
{
    QFile scriptFile(filePath);
    if (!scriptFile.open(QIODevice::WriteOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(m_fileName);
        Log.w(error);
        return false;
    }

    QTextStream out(&scriptFile);
    out << scriptText();
    return true;
}

//------------------------------------------------------------------------------
