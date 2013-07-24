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
#include <carousel/utils/TypeObjectsMap.h>

#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptConsole");
}

//------------------------------------------------------------------------------
ScriptConsole::ScriptConsole(QScriptEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
    , m_history(QStringList())
    , m_historyCommand(m_history.begin())
    , m_historyCapacity(100) // TODO: read from application references
{

}

//------------------------------------------------------------------------------
QScriptEngine *ScriptConsole::engine()
{
    return m_engine;
}

//------------------------------------------------------------------------------
bool ScriptConsole::evaluateLine(const QString &command, QString *error)
{
    addCommandToHistory(command);

    QScriptValue result = m_engine->evaluate(command);

    if (!result.isError()) {
        if (error != nullptr)
            error->clear();
        return true;
    }

    QString scriptError = QString("Script error:\n\"%1\"").arg(result.toString());
    Log.w(scriptError);

    if (error == nullptr)
        return false;

    *error = scriptError;
    return false;
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
QString ScriptConsole::historyPrev()
{
    if (m_history.isEmpty())
        return "";

    if (m_historyCommand == m_history.begin())
        return m_history.first();

    return *--m_historyCommand;
}

//------------------------------------------------------------------------------
QString ScriptConsole::historyNext()
{
    if (m_history.isEmpty())
        return "";

    if (m_historyCommand == m_history.end()) {
        return "";
    }

    if (++m_historyCommand == m_history.end()) {
        --m_historyCommand;
        return "";
    }

    return *m_historyCommand;
}

//------------------------------------------------------------------------------
const QStringList &ScriptConsole::history() const
{
    return m_history;
}

//------------------------------------------------------------------------------
void ScriptConsole::addCommandToHistory(const QString &command)
{
    if (command.trimmed().isEmpty()) {
        m_historyCommand = m_history.end(); // reset anyway
        return;
    }

    if (m_history.size() >= m_historyCapacity)
        m_history.removeFirst();

    m_history.push_back(command);
    m_historyCommand = m_history.end();
}

//------------------------------------------------------------------------------
