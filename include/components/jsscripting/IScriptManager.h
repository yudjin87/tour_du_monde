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

#ifndef ISCRIPTMANAGER_H
#define ISCRIPTMANAGER_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QObject>
#include <QtCore/QList>

class IScriptUnit;

class JSSCRIPTING_API IScriptManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<IScriptUnit *> scripts READ scripts)
public:
    typedef QList<IScriptUnit *> Scripts;

public:
    IScriptManager(){}

    virtual Scripts scripts() const = 0;

public slots:
    /*!
     * @details
     *   Takes ownership.
     */
    virtual IScriptUnit *createScript() = 0;

    /*!
     * @details
     *   Takes ownership.
     */
    virtual IScriptUnit *addScript(const QString &fileName) = 0;

    virtual void removeScript(IScriptUnit *script) = 0;

    // saves before run
    virtual void runScript(IScriptUnit *script, QString *output = nullptr, bool *error = nullptr) = 0;

    /*!
     * @details
     *   Takes ownership.
     */
    virtual Scripts addScripts(const QString &directory) = 0;

    virtual IScriptUnit *scriptByFileName(const QString &fileName) = 0;

signals:
    void scriptAdded(IScriptUnit *script);
    void scriptRemoved(IScriptUnit *script);

private:
    Q_DISABLE_COPY(IScriptManager)
};

#endif // ISCRIPTMANAGER_H
