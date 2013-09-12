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

#ifndef SCRIPTCONSOLE_H
#define SCRIPTCONSOLE_H

#include <components/jsscripting/IScriptConsole.h>

class QScriptEngine;

/*!
 * @brief
 *   It is a defaul implementation of the IScriptConsole.
 * @details
 *   There are methods similiar to the just a console or terminal - execute command
 *   and command history. But this object does not pretend for visualizatoin, there
 *   is the ScriptConsoleView for this purpose.
 *
 *   Also, when this interface is implemented, an IOutputHandler one should be implemented
 *   too to be able to redirect print() functions to the console printed() signal.
 *
 *   You can get reference to the IScriptConsole using
 * @code
 *     IScriptingService *service = serviceLocator->locate<IScriptingService>();
 *     IScriptConsole *console = service->console();
 * @endcode
 *
 * @sa ScriptConsoleView
 */
class JSSCRIPTING_API ScriptConsole : public IScriptConsole
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{ScriptConsole} using defaul QScriptEngine as an engine
     *   for command execution.
     */
    explicit ScriptConsole(QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ScriptConsole} using specified @a engine for command execution.
     *
     *   Note, that it takes ownership for engine.
     */
    explicit ScriptConsole(QScriptEngine *engine, QObject *parent = nullptr);

    /*!
     * @details
     *   Gets an script engine, that executes commands. See IScriptExtension extension,
     *   if you want to extend script engine in more common way.
     *
     * @sa execCommand
     */
    QScriptEngine *engine();

    /*!
     * @details
     *   Gets a maximum amount of commands, stored in the history collection. When current size
     *   reaches this amount, further execCommand() calls will remove oldest command from the history.
     *
     * @sa setHistoryCapacity, execCommand
     */
    int historyCapacity() const;

    /*!
     * @details
     *   Sets a maximum amount of commands, stored in the history collection.
     *
     * @sa historyCapacity, execCommand
     */
    void setHistoryCapacity(int capacity);

    /*!
     * @details
     *   Gets all executed commands on this console.
     *
     * @sa prevCommand, nextCommand
     */
    const QStringList &commandHistory() const;

public slots:
    /*!
     * @details
     *   Pushes command at the end of history, resetting history pointer (ponts to the last
     *   command) and tries to execute a @a command. Before executing the aboutToExecute() signal
     *   is emitted. If command was executed without errors, returns @a true. Otherwise, returns
     *   @a false and emits the error() signal.
     *
     *   If the number of executed commands exceeded the historyCapacity() value, then first command
     *   will be removed from the history.
     */
    bool execCommand(const QString &command);

    /*!
     * @details
     *   Moves command pointer to the previous command and returns its value.
     *   If current command is the first one - returns it and does not move
     *   pointer.
     *
     * @sa nextCommand, commandHistory
     */
    QString prevCommand();

    /*!
     * @details
     *   Moves command pointer to the next command and returns its value.
     *   If current command is the last one - returns it and does not move
     *   pointer.
     *
     * @sa prevCommand, commandHistory
     */
    QString nextCommand();

    /*!
     * @details
     *   It is invoked each time when print() is invoked from the script.
     *   A @a message is a parameter, that was passed to the JavaScript's print()
     *   function.
     */
    void print(const QString &message);

private:
    Q_DISABLE_COPY(ScriptConsole)
    void addCommandToHistory(const QString &command);

private:
    QScriptEngine *m_engine;
    QStringList m_history;
    QStringList::const_iterator m_historyCommand;
    int m_historyCapacity;
};

#endif // SCRIPTCONSOLE_H
