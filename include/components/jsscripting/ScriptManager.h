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

#include <components/jsscripting/IScriptManager.h>

class IScriptEngineFactory;

class JSSCRIPTING_API ScriptManager : public IScriptManager
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Does not takes ownership for factory;
     */
    ScriptManager(IScriptEngineFactory *factory, QObject *parent = nullptr);
    ~ScriptManager();

    Scripts scripts() const;

    IScriptUnit *scriptByFileName(const QString &fileName);

    /*!
     * @details
     *   Takes ownership.
     */
    IScriptUnit *createScript();

    /*!
     * @details
     *   Takes ownership.
     */
    IScriptUnit *addScript(const QString &fileName);

    void removeScript(IScriptUnit *script);

    /*!
     * @details
     *   Takes ownership.
     */
    Scripts addScripts(const QString &directory);

protected:
    virtual IScriptUnit *createNewScript(const QString *fileName = nullptr);

private:
    IScriptEngineFactory *m_factory;
    Scripts m_scripts;
};

#endif // SCRIPTMANAGER_H
