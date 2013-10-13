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
    , m_filePath("")
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
    , m_filePath(absolutePath(filePath))
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
bool ScriptUnit::isRunning() const
{
    if (m_engine == nullptr)
        return false;

    return m_engine->isEvaluating();
}

//------------------------------------------------------------------------------
bool ScriptUnit::isLoaded() const
{
    return m_isLoaded;
}

//------------------------------------------------------------------------------
QString ScriptUnit::fileName() const
{
    QFileInfo file(m_filePath);
    return file.fileName();
}

//------------------------------------------------------------------------------
QString ScriptUnit::scriptText() const
{
    return m_script->toPlainText();
}

//------------------------------------------------------------------------------
void ScriptUnit::setScriptText(const QString &plainText)
{
    m_script->setPlainText(plainText);
}

//------------------------------------------------------------------------------
QString ScriptUnit::absoluteFilePath() const
{
    return m_filePath;
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
void ScriptUnit::print(const QString &message)
{
    emit printed(message);
}

//------------------------------------------------------------------------------
bool ScriptUnit::load()
{
    if (m_isLoaded)
        return true;

    if (m_filePath.isEmpty()) {
        Log.w("No file name specified");
        return false;
    }

    QFile scriptFile(m_filePath);
    if (!scriptFile.open(QIODevice::ReadOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(m_filePath);
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
    m_filePath = absolutePath(filePath);
    emit fileNameChanged();
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
    return saveAs(m_filePath);
}

//------------------------------------------------------------------------------
bool ScriptUnit::saveAs(const QString &filePath)
{
    if (filePath.isEmpty())
        return false;

    if (!m_script->isModified())
        return true;

    QString fPath = absolutePath(filePath);
    if (!saveToFile(fPath))
        return false;

    m_filePath = fPath;
    emit fileNameChanged();

    m_script->setModified(false);
    return true;
}

//------------------------------------------------------------------------------
void ScriptUnit::abort()
{
    if (m_engine == nullptr)
        return;

    if (!m_engine->isEvaluating())
        return;

    m_engine->abortEvaluation();
    emit aborted();
}

//------------------------------------------------------------------------------
bool ScriptUnit::run()
{
    const QString &script = scriptText();
    if (script.isEmpty()) {
        Log.w("Empty script - nothing to evaluate");
        return false;
    }

    if (!fileName().isEmpty())
        save();

    // Do not destroy previous engine right after exiting this scope,
    // because script may still executes. So, destroy only when new run() is called
    m_engine.reset(m_factory->createEngine(this));
    QScriptValue result = m_engine->evaluate(script);
    if (!result.isError())
        return true;

    QString scriptError = QString("Script error:\"%1\"").arg(result.toString());
    Log.w(scriptError);

    emit error(result.toString());

    return false;
}

//------------------------------------------------------------------------------
QString ScriptUnit::absolutePath(const QString &filePath)
{
    QDir dir(QCoreApplication::applicationDirPath());
    return QDir::cleanPath(dir.absoluteFilePath(filePath));
}

//------------------------------------------------------------------------------
bool ScriptUnit::saveToFile(const QString &filePath)
{
    QFile scriptFile(filePath);
    if (!scriptFile.open(QIODevice::WriteOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(m_filePath);
        Log.w(error);
        return false;
    }

    QTextStream out(&scriptFile);
    out << scriptText();
    return true;
}

//------------------------------------------------------------------------------
