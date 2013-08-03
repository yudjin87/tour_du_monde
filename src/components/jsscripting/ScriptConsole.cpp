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

#include "ScriptConsole.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptConsole");
}

//------------------------------------------------------------------------------
ScriptConsole::ScriptConsole(QScriptEngine *engine, QObject *parent)
    : m_output("")
    , m_engine(engine)
    , m_history(QStringList())
    , m_historyCommand(m_history.begin())
    , m_historyCapacity(100) // TODO: read from application references
{
    setParent(parent);
    engine->setParent(this);
}

//------------------------------------------------------------------------------
ScriptConsole::ScriptConsole(QObject *parent)
    : m_output("")
    , m_engine(nullptr)
    , m_history(QStringList())
    , m_historyCommand(m_history.begin())
    , m_historyCapacity(100) // TODO: read from application references
{
    setParent(parent);
    m_engine = new QScriptEngine(this);
}

//------------------------------------------------------------------------------
QScriptEngine *ScriptConsole::engine()
{
    return m_engine;
}

//------------------------------------------------------------------------------
void ScriptConsole::execCommand(const QString &command, QString *output, bool *error)
{
    addCommandToHistory(command);

    QScriptValue result = m_engine->evaluate(command);
    if (output != nullptr)
        output->swap(m_output);

    m_output.clear();

    if (!result.isError()) {
        if (error != nullptr)
            *error = false;
        return;
    }

    QString scriptError = QString("Script error:\n\"%1\"").arg(result.toString());
    Log.w(scriptError);

    if (output != nullptr)
        *output = result.toString() + "\n";

    if (error != nullptr)
        *error = true;
}

//------------------------------------------------------------------------------
int ScriptConsole::historyCapacity() const
{
    return m_historyCapacity;
}

//------------------------------------------------------------------------------
void ScriptConsole::setHistoryCapacity(int capacity)
{
    m_historyCapacity = capacity;
}

//------------------------------------------------------------------------------
QString ScriptConsole::prevCommand()
{
    if (m_history.isEmpty())
        return "";

    if (m_historyCommand == m_history.constBegin())
        return m_history.first();

    return *--m_historyCommand;
}

//------------------------------------------------------------------------------
QString ScriptConsole::nextCommand()
{
    if (m_history.isEmpty())
        return "";

    if (m_historyCommand == m_history.constEnd()) {
        return "";
    }

    if (++m_historyCommand == m_history.constEnd()) {
        --m_historyCommand;
        return "";
    }

    return *m_historyCommand;
}

//------------------------------------------------------------------------------
const QStringList &ScriptConsole::commandHistory() const
{
    return m_history;
}

//------------------------------------------------------------------------------
QString *ScriptConsole::output()
{
    return &m_output;
}

//------------------------------------------------------------------------------
void ScriptConsole::addCommandToHistory(const QString &command)
{
    if (command.trimmed().isEmpty()) {
        m_historyCommand = m_history.constEnd(); // reset anyway
        return;
    }

    if (m_history.size() >= m_historyCapacity)
        m_history.removeFirst();

    m_history.push_back(command);
    m_historyCommand = m_history.constEnd();
}

//------------------------------------------------------------------------------
