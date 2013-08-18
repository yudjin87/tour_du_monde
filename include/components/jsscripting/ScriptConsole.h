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
 */
class JSSCRIPTING_API ScriptConsole : public IScriptConsole
{
    Q_OBJECT
public:

    explicit ScriptConsole(QObject *parent = nullptr);

    /*!
     * @details
     *  Takes ownership for engine
     */
    explicit ScriptConsole(QScriptEngine *engine, QObject *parent = nullptr);

    QScriptEngine *engine();

    /*!
     * @brief
     */
    bool execCommand(const QString &command);

    int historyCapacity() const;
    void setHistoryCapacity(int capacity);

    QString prevCommand();
    QString nextCommand();
    const QStringList &commandHistory() const;

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
