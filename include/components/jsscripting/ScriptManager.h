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

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QObject>
#include <QtCore/QMap>

class IScriptEngineFactory;
class ScriptUnit;

class JSSCRIPTING_API ScriptManager : public QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, ScriptUnit *> Scripts;

public:
    /*!
     * @details
     *   Does not takes ownership for factory;
     */
    ScriptManager(IScriptEngineFactory *factory, QObject *parent = nullptr);
    ~ScriptManager();

    /*!
     * @details
     *   Takes ownership.
     */
    ScriptUnit *addScript(const QString &fileName);

    // save before run
    void runScript(ScriptUnit *script, QString *output = nullptr, bool *error = nullptr);

    /*!
     * @details
     *   Takes ownership.
     */
    void addScripts(const QString &directory);

    Scripts scripts() const;

signals:
    void scriptAdded(ScriptUnit *script);
    void scriptRemoved(ScriptUnit *script);

private:
    IScriptEngineFactory *m_factory;
    Scripts m_scripts;
};

#endif // SCRIPTMANAGER_H
