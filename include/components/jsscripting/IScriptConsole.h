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

#ifndef ISCRIPTCONSOLE_H
#define ISCRIPTCONSOLE_H

#include <components/jsscripting/jsscripting_global.h>
#include <components/jsscripting/IOutputHandler.h>

#include <QtCore/QObject>
#include <QtCore/QStringList>

class QScriptEngine;

/*!
 * @brief
 *   This abstract class provides methods for manipulatin with scripting console
 *   object.
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
class JSSCRIPTING_API IScriptConsole : public QObject, public IOutputHandler
{
    Q_OBJECT
    Q_PROPERTY(int historyCapacity READ historyCapacity WRITE setHistoryCapacity)
    Q_PROPERTY(QStringList commandHistory READ commandHistory)
public:
    /*!
     * @details
     * @constructor{IScriptConsole}.
     */
    IScriptConsole(){}

    /*!
     * @details
     *   Gets an script engine, that executes commands. See IScriptExtension extension,
     *   if you want to extend script engine in more common way.
     *
     * @sa execCommand
     */
    virtual QScriptEngine *engine() = 0;

    /*!
     * @details
     *   Gets a maximum amount of commands, stored in the history collection. When current size
     *   reaches this amount, further execCommand() calls will remove oldest command from the history.
     *
     * @sa setHistoryCapacity, execCommand
     */
    virtual int historyCapacity() const = 0;

    /*!
     * @details
     *   Sets a maximum amount of commands, stored in the history collection.
     *
     * @sa historyCapacity, execCommand
     */
    virtual void setHistoryCapacity(int capacity) = 0;

    /*!
     * @details
     *   Gets all executed commands on this console.
     *
     * @sa prevCommand, nextCommand
     */
    virtual const QStringList &commandHistory() const = 0;

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
    virtual bool execCommand(const QString &command) = 0;

    /*!
     * @details
     *   Moves command pointer to the previous command and returns its value.
     *   If current command is the first one - returns it and does not move
     *   pointer.
     *
     * @sa nextCommand, commandHistory
     */
    virtual QString prevCommand() = 0;

    /*!
     * @details
     *   Moves command pointer to the next command and returns its value.
     *   If current command is the last one - returns it and does not move
     *   pointer.
     *
     * @sa prevCommand, commandHistory
     */
    virtual QString nextCommand() = 0;

signals:
    /*!
     * @details
     *   This signal is emmited before a @a command will be evaluated.
     *   Connect to this signal if you want to echo commands, for example,
     *   into text edit.
     */
    void aboutToExecute(const QString &command);

    /*!
     * @details
     *   This signal is emmited when the print() function is called from the script.
     *   Connect to this signal if you want to echo message, for example,
     *   into text edit.
     */
    void printed(const QString &message);

    /*!
     * @details
     *   This signal is emmited when the error is appears during evaluate the script.
     *   Connect to this signal if you want to echo error, for example,
     *   into text edit.
     */
    void error(const QString &error); // TODO: rename it!

private:
    Q_DISABLE_COPY(IScriptConsole)
};

#endif // ISCRIPTCONSOLE_H
