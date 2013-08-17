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

#include <QtCore/QObject>
#include <QtCore/QStringList>

class QScriptEngine;

/*!
 * @brief
 */
class JSSCRIPTING_API IScriptConsole : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int historyCapacity READ historyCapacity WRITE setHistoryCapacity)
    Q_PROPERTY(QStringList commandHistory READ commandHistory)
public:
    IScriptConsole(){}

    virtual QScriptEngine *engine() = 0;

    // virtual QStringList tryToComplete(const QString &command) = 0;

    virtual int historyCapacity() const = 0;
    virtual void setHistoryCapacity(int capacity) = 0;

    virtual const QStringList &commandHistory() const = 0;

public slots:
    /*!
     * @brief
     */
    virtual bool execCommand(const QString &command, QString *output = nullptr) = 0;

    virtual QString prevCommand() = 0;
    virtual QString nextCommand() = 0;


private:
    Q_DISABLE_COPY(IScriptConsole)
};

#endif // ISCRIPTCONSOLE_H
